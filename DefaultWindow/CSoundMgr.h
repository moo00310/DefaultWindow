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
    FMOD::Studio::EventInstance* PlayEvent(const char* _EventPath); // ?´ë²¤?¸ë? ?¬ìƒ?˜ê³  ê·??´ë²¤?¸ì˜ ?¬ì¸?°ë? ë°˜í™˜
    FMOD::Studio::Bank* LoadBank(const char* _BankFilePath); // ë±…í¬ë¥?ë¡œë“œ?˜ê³  ê·?ë±…í¬???¬ì¸?°ë? ë°˜í™˜
    // Bank ?Œì¼?€ Fmod ?¤íŠœ?”ì˜¤?ì„œ ë¹Œë“œ???¤ë””???°ì´?°ë? ?€?¥í•˜??ì»¨í…Œ?´ë„ˆë¡? 
    // ?¬ìš© ?? ???´ìƒ ?„ìš”?†ì–´ì§?Bank???¬ì˜ ë¦´ë¦¬ì¦ˆì—??Unload ?¨ìˆ˜ë¥??¸ì¶œ?´ì£¼?´ì•¼ ?œë‹¤.
    void Stop_All_Event();

private:
    static CSoundMgr* m_pInstance;

    FMOD::System* m_pCoreSystem; // ?˜ì—…???¬ìš©?ˆë˜ ê¸°ë³¸ Fmod ì½”ì–´ ?œìŠ¤??
    FMOD::Studio::System* m_pStudioSystem; // Fmod Studio?€ ?°ë™???„í•´ ?„ìš”???¤íŠœ?”ì˜¤ ?œìŠ¤??
};
