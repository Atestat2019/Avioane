#include "ScriereFisier.h"
#include "Avioane.h"
#include "Core/Public/Misc/FileHelper.h"
#include "Core/Public/Misc/Paths.h"

bool UScriereFisier::LoadTxt(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::GameDir() + FileNameA));
}

bool UScriereFisier::SaveTxt(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::GameDir() + FileNameB));
}