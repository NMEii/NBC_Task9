// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CXChatInput.generated.h"

/**
 * 
 */
UCLASS()
class CHATX_API UCXChatInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	virtual void NativeDestruct() override;
	
protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextBox_ChatInput;
};
