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
    FMOD::Studio::EventInstance* PlayEvent(const char* _EventPath); // ?�벤?��? ?�생?�고 �??�벤?�의 ?�인?��? 반환
    FMOD::Studio::Bank* LoadBank(const char* _BankFilePath); // 뱅크�?로드?�고 �?뱅크???�인?��? 반환
    // Bank ?�일?� Fmod ?�튜?�오?�서 빌드???�디???�이?��? ?�?�하??컨테?�너�? 
    // ?�용 ?? ???�상 ?�요?�어�?Bank???�의 릴리즈에??Unload ?�수�??�출?�주?�야 ?�다.
    void Stop_All_Event();

private:
    static CSoundMgr* m_pInstance;

    FMOD::System* m_pCoreSystem; // ?�업???�용?�던 기본 Fmod 코어 ?�스??
    FMOD::Studio::System* m_pStudioSystem; // Fmod Studio?� ?�동???�해 ?�요???�튜?�오 ?�스??
};
