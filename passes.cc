#include <gcc-plugin.h>
#include <cassert>
#include <unordered_map>
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tree.h"
#include <cp/cp-tree.h>//name-lookup.h>
#include <plugin-version.h>
#include <tree-pass.h>

#include <iostream>

// Required symbol.
int plugin_is_GPL_compatible;


namespace {

  plugin_info my_plugin_info = {
    VERSION,
    "passes plugin"
  };


  int last_pass_type = -1;
  std::unordered_map<opt_pass*,int> levels;


  void record_hierarchy(opt_pass* pass, int level = 0)
  {
    levels[pass] = level;
    if (pass->sub != nullptr)
      record_hierarchy(pass->sub, level + 1);
    if (pass->next != nullptr)
      record_hierarchy(pass->next, level);
  }


  void pass_execution_cb(void *gcc_data, void *user_data)
  {
    opt_pass* pass = (opt_pass*) gcc_data;

    if (levels.find(pass) == levels.end())
      record_hierarchy(pass);

    if (last_pass_type != pass->type) {
      switch (pass->type) {
      case GIMPLE_PASS:
        std::cerr << "GIMPLE pass:\n";
        break;
      case RTL_PASS:
        std::cerr << "RTL pass:\n";
        break;
      case SIMPLE_IPA_PASS:
        std::cerr << "simple IPA pass:\n";
        break;
      case IPA_PASS:
        std::cerr << "IPA pass:\n";
        break;
      }
      last_pass_type = pass->type;
    }

    std::cout << "    pass ";
    for (int i = 0; i < levels[pass]; ++i)
      std::cout << "   ";
     std::cout << pass->name << std::endl;
  }


} // anonymous namespace


int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version)
{
  if (! plugin_default_version_check(version, &gcc_version))
    return 1;

  register_callback(plugin_info->base_name, PLUGIN_INFO, nullptr, &my_plugin_info);

  // Register all the callback functions.
  register_callback(plugin_info->base_name, PLUGIN_PASS_EXECUTION, pass_execution_cb, nullptr);

  // Add more here if necessary.

  return 0;
}
