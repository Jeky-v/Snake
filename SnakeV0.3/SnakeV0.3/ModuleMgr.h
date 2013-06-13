#pragma once
#include <string>
#include <map>
#include "IModule.h"


class ModuleMgr
{
public:
  ModuleMgr();

  void AddModule(const std::string &name, IModule *module);
  void SetActiveModule(const std::string &name);
  std::string getCurrentModuleName();
  bool Frame();
  void Close();

private:
  std::map<std::string, IModule*> m_moduleList;
  IModule *m_currmodule;
};


