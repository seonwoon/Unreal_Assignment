#include "MiniGameMode.h"
#include "MiniCharacter.h"
#include "MiniPlayerController.h" 
#include "MiniGameState.h"// PlayerController 클래스를 사용

AMiniGameMode::AMiniGameMode()
{
	DefaultPawnClass = AMiniCharacter::StaticClass();
	PlayerControllerClass = AMiniPlayerController::StaticClass();
	GameStateClass = AMiniGameState::StaticClass();

}