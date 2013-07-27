#pragma once

class ModuleMgr;

class IModule
{
public:
  IModule();
  virtual ~IModule(){}

  void Init();
  bool Frame();
  void Close();

  void SetMgr(ModuleMgr *mgr){m_mgr = mgr;}
  ModuleMgr* getModuleMgr(){return m_mgr;}

  bool IsExit() const {return !m_isexit;}
  void Exit(){m_isexit=true;}

  virtual void doInit() = 0;
  virtual bool doRun() = 0;
  virtual void doClose() = 0;

protected:  
  ModuleMgr *m_mgr;  // указатель на менеджер сцен
  bool m_isinit;    // флаг сообщающий о инициализации 
  bool m_isexit;    // флаг оповещающий о выходе  
};