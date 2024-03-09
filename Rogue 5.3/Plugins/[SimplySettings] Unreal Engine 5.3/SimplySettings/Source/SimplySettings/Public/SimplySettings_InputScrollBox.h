// Copyright Phoinix-DEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ScrollBox.h"
#include "PlayerMappableKeySettings.h"
#include "InputMappingContext.h"
#include "SimplySettings_InputScrollBox.generated.h"

/**
 * Represents a single Key Mapping Row, mainly used for auto generation
 */
USTRUCT(BlueprintType)
struct FInputRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	FText DisplayRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	UInputMappingContext *Context1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	UInputMappingContext *Context2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	UInputMappingContext *Context3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	FEnhancedActionKeyMapping Mapping1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	FEnhancedActionKeyMapping Mapping2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simply Settings")
	FEnhancedActionKeyMapping Mapping3;

	void RefreshDisplayRowName()
	{
		if (Mapping1.GetPlayerMappableKeySettings())
		{
			DisplayRowName = Mapping1.GetPlayerMappableKeySettings()->DisplayName;
		}
		if (DisplayRowName.IsEmpty())
		{
			if (Mapping2.GetPlayerMappableKeySettings())
			{
				DisplayRowName = Mapping2.GetPlayerMappableKeySettings()->DisplayName;
			}
		}
		if (DisplayRowName.IsEmpty())
		{
			if (Mapping2.GetPlayerMappableKeySettings())
			{
				DisplayRowName = Mapping3.GetPlayerMappableKeySettings()->DisplayName;
			}
		}
	}
};

/**
 * Used to bundle mappings together into categories, to display them together
 */
USTRUCT(BlueprintType)
struct FInputCategory
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Simply Settings")
	TArray<FInputRow> Rows;

	UPROPERTY(BlueprintReadWrite, Category = "Simply Settings")
	FText DisplayCategory;

	void AddMapping(UInputMappingContext *Context, FEnhancedActionKeyMapping Mapping, int Coll)
	{

		int Index = Rows.IndexOfByPredicate([Mapping](FInputRow Row)
											{
												UPlayerMappableKeySettings *Settings = Mapping.GetPlayerMappableKeySettings();
												if (Settings)
												{
													return Row.DisplayRowName.EqualTo(Settings->DisplayName);
												}
												return false; });
		if (Index >= 0)
		{
			switch (Coll)
			{
			case 1:
				Rows[Index].Mapping1 = Mapping;
				Rows[Index].Context1 = Context;
				break;
			case 2:
				Rows[Index].Mapping2 = Mapping;
				Rows[Index].Context2 = Context;
				break;
			case 3:
				Rows[Index].Mapping3 = Mapping;
				Rows[Index].Context3 = Context;
				break;
			default:
				checkf(false, TEXT("Currently, max. 3 colls are supported"));
			}
			Rows[Index].RefreshDisplayRowName();
		}
		else
		{
			FInputRow NewInputRow = FInputRow();
			UPlayerMappableKeySettings *Settings = Mapping.GetPlayerMappableKeySettings();
			if (Settings)
			{
				NewInputRow.DisplayRowName = Settings->DisplayName;
			}

			switch (Coll)
			{
			case 1:
				NewInputRow.Context1 = Context;
				NewInputRow.Mapping1 = Mapping;
				break;
			case 2:
				NewInputRow.Context2 = Context;
				NewInputRow.Mapping2 = Mapping;
				break;
			case 3:
				NewInputRow.Context3 = Context;
				NewInputRow.Mapping3 = Mapping;
				break;
			default:
				checkf(false, TEXT("Currently, max. 3 colls are supported"));
			}

			NewInputRow.RefreshDisplayRowName();
			Rows.Add(NewInputRow);
		}
		RefreshDisplayCategory();
	}

	void RefreshDisplayCategory()
	{
		if (Rows.Num() > 0)
		{
			if (DisplayCategory.IsEmpty() && Rows[0].Mapping1.GetPlayerMappableKeySettings())
			{
				DisplayCategory = Rows[0].Mapping1.GetPlayerMappableKeySettings()->DisplayCategory;
			}
			if (DisplayCategory.IsEmpty() && Rows[0].Mapping2.GetPlayerMappableKeySettings())
			{
				DisplayCategory = Rows[0].Mapping2.GetPlayerMappableKeySettings()->DisplayCategory;
			}
			if (DisplayCategory.IsEmpty() && Rows[0].Mapping3.GetPlayerMappableKeySettings())
			{
				DisplayCategory = Rows[0].Mapping3.GetPlayerMappableKeySettings()->DisplayCategory;
			}
		}
	}
};

/**
 * Defines the priority of a category, used for the autogenerate
 */
USTRUCT(BlueprintType)
struct FInputCategorySortingPriority
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	FText DisplayCategory;

	UPROPERTY(EditAnywhere, Category = "Simply Settings")
	int SortingPriority;

public:
	FInputCategorySortingPriority() {}

	FInputCategorySortingPriority(FText InDisplayCategory, int InSortingPriority)
	{
		DisplayCategory = InDisplayCategory;
		SortingPriority = InSortingPriority;
	}
};

UCLASS()
class SIMPLYSETTINGS_API USimplySettings_InputScrollBox : public UScrollBox
{
	GENERATED_BODY()

public:
	// Whether the key selector should automatically be created
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Enable Auto Generate (Experimental)"), Category = "Setup")
	bool EnableAutoGenerate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	TArray<UInputMappingContext *> Contexts_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	TArray<UInputMappingContext *> Contexts_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	TArray<UInputMappingContext *> Contexts_3;

	// This generates the categories with the default priority
	// WARNING: This adds them to your existing categories / priorities
	UPROPERTY(EditAnywhere, Category = "Setup", Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	bool Generate_Categories = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	TArray<FInputCategorySortingPriority> CategoriesSorting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (EditCondition = "EnableAutoGenerate"))
	FName DefaultCategoryName = FName("General");

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent &PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	void ExecuteAutoGenerate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Simply Settings")
	void ExecuteAutoGenerateEvent(const TArray<FInputCategory> &InputCategories);

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	int GetNumberOfCols() const;

	/**
	 * Generates and sets categories for the given contexts
	 * WARNING: This adds them to your existing categories / priorities
	 */
	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	virtual void GenerateCategories();

	UFUNCTION(BlueprintCallable, Category = "Simply Settings")
	virtual int GetCategorySortPriority(FText DisplayCategory) const;

private:
	void AppendMappings(TArray<UInputMappingContext *> Contexts, TMap<FString, FInputCategory> &Categories, int Row);

	TArray<FInputCategory> GetCategories();
};
