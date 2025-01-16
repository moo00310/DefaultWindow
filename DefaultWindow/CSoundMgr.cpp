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

    // �⺻������ �׻� �ʿ��� Bank�� �ε�
    LoadBank("../sound/Build/Desktop/Master.bank");
    LoadBank("../sound/Build/Desktop/Master.strings.bank");
    //LoadBank("./examples/Build/Desktop/Music.bank");
    //LoadBank("./examples/Build/Desktop/SFX.bank");
}
void CSoundMgr::Update()
{
    m_pStudioSystem->update();
    m_pCoreSystem->update();
    // �����߿���.
}
void CSoundMgr::Release()
{
    m_pStudioSystem->release();
    m_pCoreSystem->release();
    // �����߿���.
}

FMOD::Studio::EventInstance* CSoundMgr::PlayEvent(const char* _EventPath)
{
    FMOD::Studio::EventDescription* pEventDescription; // �̺�Ʈ�� ������ �����ϴ� Ŭ����
    FMOD_RESULT result = m_pStudioSystem->getEvent(_EventPath, &pEventDescription); // �ý������� ���� �̸��� ���� �̺�Ʈ�� ������ �޾ƿ´�.

    FMOD::Studio::EventInstance* pEventInstance = nullptr;
    pEventDescription->createInstance(&pEventInstance); // �̺�Ʈ �ν��Ͻ� ����
    result = pEventInstance->start();
    pEventInstance->setCallback(AutoRelease, FMOD_STUDIO_EVENT_CALLBACK_STOPPED); // �̺�Ʈ�� ������ AutoRelease�Լ��� ���� �ڵ����� �޸𸮸� ��ȯ���ش�.

    m_pStudioSystem->update();
    return pEventInstance;
}

FMOD::Studio::Bank* CSoundMgr::LoadBank(const char* _BankFilePath)
{
    FMOD::Studio::Bank* pBank = nullptr;
    FMOD_RESULT result = m_pStudioSystem->loadBankFile(_BankFilePath, FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank);
    return pBank;
}

FMOD_RESULT F_CALLBACK AutoRelease(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* eventInstance, void* parameters) // ����� ���� �̺�Ʈ �ڵ� ��ȯ�� ����
{
    reinterpret_cast<FMOD::Studio::EventInstance*>(eventInstance)->release(); // FMOD �ݹ��Լ��� C�� C++�� ������ ����� �ϱ� ���� ����ü �����͸� �⺻ �Ű������� ����.
    //�̶����� C++������ reinterpret_cast�� ���� Ŭ���� �����ͷ� ����ȯ �����־����.
    return FMOD_OK;
}