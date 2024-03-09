// Copyright Phoinix-DEV

#include "SimplySettings_InputScrollBox.h"
#include "Kismet/KismetTextLibrary.h"

#if WITH_EDITOR
void USimplySettings_InputScrollBox::PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.Property != nullptr && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(USimplySettings_InputScrollBox, Generate_Categories))
	{
		GenerateCategories();
		Generate_Categories = false;
	}
}
#endif

void USimplySettings_InputScrollBox::GenerateCategories()
{
	int Priority = 1000;
	TArray<FInputCategory> Categories = GetCategories();
	for (FInputCategory C : Categories)
	{
		FText DisplayCategory = C.DisplayCategory;
		Priority += 10;

		FInputCategorySortingPriority Prio = FInputCategorySortingPriority(DisplayCategory, Priority);
		CategoriesSorting.Add(Prio);
	}
}

int USimplySettings_InputScrollBox::GetCategorySortPriority(FText DisplayCategory) const
{
	if (DisplayCategory.IsEmpty())
	{
		DisplayCategory = FText::FromString(DefaultCategoryName.ToString());
	}
	TArray<FInputCategorySortingPriority> Cat = CategoriesSorting.FilterByPredicate([DisplayCategory](const FInputCategorySortingPriority &Prio)
																					{ return UKismetTextLibrary::EqualEqual_TextText(Prio.DisplayCategory, DisplayCategory); });

	if (Cat.Num() > 0)
	{
		return Cat[0].SortingPriority;
	}
	return -1;
}

int USimplySettings_InputScrollBox::GetNumberOfCols() const
{
	int counter = 0;
	if (Contexts_1.Num() > 0)
	{
		counter++;
	}
	if (Contexts_2.Num() > 0)
	{
		counter++;
	}
	if (Contexts_3.Num() > 0)
	{
		counter++;
	}
	return counter;
}

void USimplySettings_InputScrollBox::ExecuteAutoGenerate()
{
	if (EnableAutoGenerate)
	{
		TArray<FInputCategory> Categories = GetCategories();
		Categories.Sort([this](FInputCategory A, FInputCategory B)
						{ return GetCategorySortPriority(A.DisplayCategory) < GetCategorySortPriority(B.DisplayCategory); });

		ExecuteAutoGenerateEvent(Categories);
	}
}

void USimplySettings_InputScrollBox::AppendMappings(TArray<UInputMappingContext *> Contexts, TMap<FString, FInputCategory> &Categories, int Coll)
{
	for (UInputMappingContext *Context : Contexts)
	{
		if (!IsValid(Context))
		{
			continue;
		}
		for (FEnhancedActionKeyMapping Mapping : Context->GetMappings())
		{
			FString CurrentCategory;
			if (!Mapping.GetPlayerMappableKeySettings())
			{
				continue;
			}

			CurrentCategory = Mapping.GetPlayerMappableKeySettings()->DisplayCategory.ToString();

			FInputCategory *InputCategory = Categories.Find(CurrentCategory);
			if (InputCategory)
			{
				InputCategory->AddMapping(Context, Mapping, Coll);
			}
			else
			{
				FInputCategory NewCategory = FInputCategory();
				NewCategory.AddMapping(Context, Mapping, Coll);
				Categories.Add(CurrentCategory, NewCategory);
			}
		}
	}
}

TArray<FInputCategory> USimplySettings_InputScrollBox::GetCategories()
{
	TMap<FString, FInputCategory> Categories;

	AppendMappings(Contexts_1, Categories, 1);
	AppendMappings(Contexts_2, Categories, 2);
	AppendMappings(Contexts_3, Categories, 3);

	TArray<FInputCategory> Out;
	Categories.GenerateValueArray(Out);
	return Out;
}
