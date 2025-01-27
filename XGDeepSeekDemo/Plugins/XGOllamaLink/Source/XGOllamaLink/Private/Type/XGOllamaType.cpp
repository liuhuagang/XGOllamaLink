// Copyright 2025 Xiao Gang. All Rights Reserved.

#include "XGOllamaType.h"

#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "JsonObjectConverter.h"

FString FXGOllamaReqInfo::ToJsonString()
{
    FString OutJson =TEXT("");

    FJsonObjectConverter::UStructToJsonObjectString(*this, OutJson);


    return OutJson;
}
