#include "GameMode/GameModeRunner.h"
#include "../../../../Source/Runner/Public/Actors/Floors/FloorTile.h"

void AGameModeRunner::BeginPlay()
{
	CreateInitialFloorTiles();
}

void AGameModeRunner::CreateInitialFloorTiles()
{
	AFloorTile* Tile = AddFloorTile(false);

	if (Tile)
	{
		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}

	//for (float Val : LaneSwitchValues)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %f"), Val);
	//}

	AddFloorTile(false);
	AddFloorTile(false);


	for (int i = 0; i < NumItinitalFloorTiles; i++)
	{
		AddFloorTile(true);
	}
}

void AGameModeRunner::UpdateScore(float deltaTime)
{
	// 1 de score = 1 seconde
	LevelScore += 1.0f * deltaTime / 1.0f;
}

float AGameModeRunner::GetScore()
{
	return LevelScore;
}

float AGameModeRunner::GetCoins()
{
	return TotalCoins;
}

AFloorTile* AGameModeRunner::AddFloorTile(const bool bSpawnItems)
{
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorTile* Tile = World->SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);

		if (Tile)
		{
			if (bSpawnItems)
			{
				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTransform();
		}

		return Tile;
	}

	return nullptr;

}

void AGameModeRunner::AddCoin()
{
	TotalCoins += 1;

	UE_LOG(LogTemp, Warning, TEXT("TOTAL COINS: %d"), TotalCoins);
}

void AGameModeRunner::ResetScore()
{
	LevelScore = 0.f;
}

//void AGameModeRunner::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	UpdateScore(DeltaTime);
//
//}
