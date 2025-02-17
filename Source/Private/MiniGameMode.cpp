#include "MiniGameMode.h"
#include "MiniCharacter.h"
#include "MiniPlayerController.h" 
#include "MiniGameState.h"// PlayerController Ŭ������ ���

AMiniGameMode::AMiniGameMode()
{
	DefaultPawnClass = AMiniCharacter::StaticClass();
	PlayerControllerClass = AMiniPlayerController::StaticClass();
	GameStateClass = AMiniGameState::StaticClass();

}