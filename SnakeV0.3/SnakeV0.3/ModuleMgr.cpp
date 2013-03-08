#include "ModuleMgr.h"

ModuleMgr::ModuleMgr() :m_currmodule(nullptr)
{
}

void ModuleMgr::AddModule(const std::string &name, IModule *module)
{
  m_moduleList.insert(std::pair<std::string,IModule*>(name, module));
}

void ModuleMgr::SetActiveModule(const std::string &name)
{
  if (m_currmodule)
    m_currmodule->Close();

  auto it = m_moduleList.find(name);
  if (it == m_moduleList.end())
    return;

  m_currmodule = it->second;
  if (m_currmodule)
  {
    m_currmodule->SetMgr(this);
    m_currmodule->Init();
  }
}

bool ModuleMgr::Frame()
{
  if (!m_currmodule)
    return false;

  return m_currmodule->Frame();
}

void ModuleMgr::Close()
{
  if (m_currmodule)
    m_currmodule->Close();
  
  m_moduleList.clear();
}
