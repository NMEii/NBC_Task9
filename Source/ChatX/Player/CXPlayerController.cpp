// Fill out your copyright notice in the Description page of Project Settings.


#include "CXPlayerController.h"

#include "ChatX.h"
#include "CXPlayerState.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Game/CXGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/CXChatInput.h"
#include "Net/UnrealNetwork.h"

ACXPlayerController::ACXPlayerController()
{
	bReplicates = true;
}

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() == false)
	{
		return;
	}
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	
	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
	
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, NotificationText);
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	
	//PrintChatMessageString(ChatMessageString);
	if (IsLocalController() == true)
	{
		//ServerRPCPrintChatMessageString(InChatMessageString);
		ACXPlayerState* CXPS = GetPlayerState<ACXPlayerState>();
		if (IsValid(CXPS) == true)
		{
			FString CombinedChatMessageString = CXPS->GetPlayerInfoString() + TEXT(" : ") + InChatMessageString;
			
			ServerRPCPrintChatMessageString(CombinedChatMessageString);
		}
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	//UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
	
	// FString NetModeString = ChatXFunctionLibrary::GetNetModeString(this);
	// FString CombinedMessageString = FString::Printf(TEXT("%s : %s"), *NetModeString, *InChatMessageString);
	// ChatXFunctionLibrary::MyPrintString(this, CombinedMessageString, 10.0f);
	
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.0f);
}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	// for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
	// {
	// 	ACXPlayerController* CXPlayerController = *It;
	// 	if (IsValid(CXPlayerController) == true)
	// 	{
	// 		CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	// 	}
	// }
	
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ACXGameModeBase* CXGM = Cast<ACXGameModeBase>(GM);
		if (IsValid(CXGM) == true)
		{
			CXGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}
