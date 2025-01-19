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
    FMOD::Studio::EventInstance* PlayEvent(const char* _EventPath); // 이벤트를 재생하고 그 이벤트의 포인터를 반환
    FMOD::Studio::Bank* LoadBank(const char* _BankFilePath); // 뱅크를 로드하고 그 뱅크의 포인터를 반환
    // Bank 파일은 Fmod 스튜디오에서 빌드한 오디오 데이터를 저장하는 컨테이너로, 
    // 사용 후, 더 이상 필요없어진 Bank는 씬의 릴리즈에서 Unload 함수를 호출해주어야 한다.

private:
    static CSoundMgr* m_pInstance;

    FMOD::System* m_pCoreSystem; // 수업때 사용했던 기본 Fmod 코어 시스템
    FMOD::Studio::System* m_pStudioSystem; // Fmod Studio와 연동을 위해 필요한 스튜디오 시스템
};
