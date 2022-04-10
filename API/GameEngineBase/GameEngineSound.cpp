#include "GameEngineSound.h"
#include "GameEnginePath.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

#pragma comment(lib,"fmod_vc.lib")

FMOD::System* SoundSystem_ = nullptr;

std::map<std::string, GameEngineSound*> GameEngineSound::AllRes;

class SoundSystemCreater
{
public:
    SoundSystemCreater()
    {
        FMOD::System_Create(&SoundSystem_);
        
        if (SoundSystem_ == nullptr)
        {
            MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
            return;
        }

        //���� ī���� ������ ������
        if (SoundSystem_->init(32, FMOD_DEFAULT, nullptr) != FMOD_OK)
        {
            MsgBoxAssert("���� �ý��� ������ �����߽��ϴ�.");
            return;
        }
    }
};

SoundSystemCreater CreatInst = SoundSystemCreater();

GameEngineSound::GameEngineSound()
    :Sound(nullptr)
{
}

GameEngineSound::~GameEngineSound()
{
}

bool GameEngineSound::Load(const std::string& _Path)
{
    if (SoundSystem_->createSound(_Path.c_str(), FMOD_LOOP_NORMAL, nullptr, &Sound) != FMOD_OK)
    {
        MsgBoxAssertString("���� �ε忡 �����߽��ϴ� : " + _Path);
        return false;
    }

    return true;
}

//��� �Ŵ�����Ʈ
void GameEngineSound::SoundPlayOneShot(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    GameEngineSound* FindSound = FindRes(UpperName);

    if (FindSound == nullptr)
    {
        MsgBoxAssertString("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ� \n �̸� : " + UpperName);
        return;
    }

    SoundSystem_->playSound(FindSound->Sound, nullptr, false, nullptr);
}

GameEngineSoundPlayer GameEngineSound::SoundPlayControl(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    GameEngineSound* FindSound = FindRes(UpperName);

    if (nullptr == FindSound)
    {
        MsgBoxAssertString("�������� �ʴ� ���带 ����Ϸ��� �߽��ϴ�.\n �̸� : " + UpperName);
        return GameEngineSoundPlayer();
    }

    FMOD::Channel* PlayControl = nullptr;

    SoundSystem_->playSound(FindSound->Sound, nullptr, false, &PlayControl);

    return GameEngineSoundPlayer(FindSound, PlayControl);
}

void GameEngineSound::Update()
{
    if (SoundSystem_ == nullptr)
    {
        return;
    }

    SoundSystem_->update();
}

GameEngineSound* GameEngineSound::FindRes(const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    std::map<std::string, GameEngineSound*>::iterator FindIter = AllRes.find(UpperName);

    if (FindIter == AllRes.end())
    {
        return nullptr;
    }

    return FindIter->second;
}

GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path)
{
    GameEnginePath NewPath = GameEnginePath(_Path);
    return LoadRes(_Path, NewPath.GetFileName());
}

GameEngineSound* GameEngineSound::LoadRes(const std::string& _Path, const std::string& _Name)
{
    std::string UpperName = GameEngineString::ToUpperReturn(_Name);

    GameEngineSound* NewRes = new GameEngineSound();

    if (false == NewRes->Load(_Path))
    {
        delete NewRes;
        NewRes = nullptr;
        return nullptr;
    }

    AllRes.insert(std::make_pair(UpperName, NewRes));
    return nullptr;
}

void GameEngineSound::AllResoucesDestroy()
{
    for (std::pair<std::string, GameEngineSound*> Res : AllRes)
    {
        delete Res.second;
        Res.second = nullptr;
    }

    AllRes.clear();

    if (nullptr != SoundSystem_)
    {
        SoundSystem_->release();
        SoundSystem_ = nullptr;
    }
}

//���� �÷��̾�
void GameEngineSoundPlayer::Stop()
{
    if (ControlHandle_ == nullptr)
    {
        MsgBoxAssert("���� ��Ʈ�� ä���� ���� ���¿��� Stop�� �Ϸ��߽��ϴ� \n");
        return;
    }

    ControlHandle_->stop();
}

GameEngineSoundPlayer::GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other)
    : Sound_(_Other.Sound_)
    , ControlHandle_(_Other.ControlHandle_)
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer(GameEngineSound* Sound, FMOD::Channel* ControlHandle)
    :Sound_(Sound),
    ControlHandle_(ControlHandle)
{
}

GameEngineSoundPlayer::GameEngineSoundPlayer()
    : Sound_(nullptr)
    , ControlHandle_(nullptr)
{
}

GameEngineSoundPlayer::~GameEngineSoundPlayer()
{
}
