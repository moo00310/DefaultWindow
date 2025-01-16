#pragma once
#pragma once
#include "Define.h"

#define MAX_SFX_CHANNEL 31
FMOD_RESULT F_CALLBACK AutoRelease(FMOD_STUDIO_EVENT_CALLBACK_TYPE type, FMOD_STUDIO_EVENTINSTANCE* eventInstance, void* parameters);

class CSoundMgr
{
public:
    static CSoundMgr* Get_Instance()
    {
        if (nullptr == m_pInstance)
            m_pInstance = new CSoundMgr;

        return m_pInstance;
    }
    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

private:
    CSoundMgr();
    ~CSoundMgr();

public:
    void Initialize();
    void Update();
    void Release();

public:
    FMOD::Studio::EventInstance* PlayEvent(const char* _EventPath); // �̺�Ʈ�� ����ϰ� �� �̺�Ʈ�� �����͸� ��ȯ
    FMOD::Studio::Bank* LoadBank(const char* _BankFilePath); // ��ũ�� �ε��ϰ� �� ��ũ�� �����͸� ��ȯ
    // Bank ������ Fmod ��Ʃ������� ������ ����� �����͸� �����ϴ� �����̳ʷ�, 
    // ��� ��, �� �̻� �ʿ������ Bank�� ���� ������� Unload �Լ��� ȣ�����־�� �Ѵ�.

private:
    static CSoundMgr* m_pInstance;

    FMOD::System* m_pCoreSystem; // ������ ����ߴ� �⺻ Fmod �ھ� �ý���
    FMOD::Studio::System* m_pStudioSystem; // Fmod Studio�� ������ ���� �ʿ��� ��Ʃ��� �ý���
};
