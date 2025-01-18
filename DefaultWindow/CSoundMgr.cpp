#include "pch.h"
#include "CSoundMgr.h"


CSoundMgr* CSoundMgr::m_pInstance = nullptr;

CSoundMgr::CSoundMgr() : m_pStudioSystem(nullptr), m_pCoreSystem(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
    Release();
}

void CSoundMgr::Initialize()
{
    FMOD::Studio::System::create(&m_pStudioSystem);
    m_pStudioSystem->getCoreSystem(&m_pCoreSystem);
    m_pStudioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);

    // 기본적으로 항상 필요한 Bank들 로드
    LoadBank("../sound/Build/Desktop/Master.bank");
    LoadBank("../sound/Build/Desktop/Master.strings.bank");
   
    //LoadBank("./examples/Build/Desktop/Music.bank");
    //LoadBank("./examples/Build/Desktop/SFX.bank");
}
void CSoundMgr::Update()
{
    m_pStudioSystem->update();
    m_pCoreSystem->update();
    // 서순중요함.
}
void CSoundMgr::Release()
{
    m_pStudioSystem->release();
    m_pCoreSystem->release();
    // 서순중요함.
}

FMOD::Studio::EventInstance* CSoundMgr::PlayEvent(const char* _EventPath)
{
    FMOD::Studio::EventDescription* pEventDescription; // 이벤트의 정보를 저장하는 클래스
    FMOD_RESULT result = m_pStudioSystem->getEvent(_EventPath, &pEventDescription); // 시스템으로 부터 이름을 통해 이벤트의 정보를 받아온다.

    FMOD::Studio::EventInstance* pEventInstance = nullptr;
    pEventDescription->createInstance(&pEventInstance); // 이벤트 인스턴스 생성
    result = pEventInstance->start();
    pEventInstance->setCallback(AutoRelease, FMOD_STUDIO_EVENT_CALLBACK_STOPPED); // 이벤트가 끝나면 AutoRelease함수를 통해 자동으로 메모리를 반환해준다.

    m_pStudioSystem->update();
    return pEventInstance;
}

FMOD::Studio::Bank* CSoundMgr::LoadBank(const char* _BankFilePath)
{
    FMOD::Studio::Bank* pBank = nullptr;
    FMOD_RESULT result = m_pStudioSystem->loadBankFile(_BankFilePath, FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank);
    return pBank;
}

FMOD_RESULT F_CALLBACK AutoRelease(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* eventInstance, void* parameters) // 재생이 끝난 이벤트 자동 반환을 위한
{
    reinterpret_cast<FMOD::Studio::EventInstance*>(eventInstance)->release(); // FMOD 콜백함수는 C와 C++의 범용적 사용을 하기 위해 구조체 포인터를 기본 매개변수로 잡음.
    //이때문에 C++에서는 reinterpret_cast를 통해 클래스 포인터로 형변환 시켜주어야함.
    return FMOD_OK;
}