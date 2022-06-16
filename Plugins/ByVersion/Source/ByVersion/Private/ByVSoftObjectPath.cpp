// Copyright Byteyang Games, Inc. All Rights Reserved.

#include "ByVSoftObjectPath.h"

FString FByVSoftObjectPath::ToString() const
{
	return SoftObjectPath.ToString();
}

void FByVSoftObjectPath::ToString(FStringBuilderBase& Builder) const
{
	return SoftObjectPath.ToString(Builder);
}

void FByVSoftObjectPath::SetPath(FWideStringView Path)
{
	SoftObjectPath.SetPath(Path);
}

void FByVSoftObjectPath::SetPath(FAnsiStringView Path)
{
	SoftObjectPath.SetPath(Path);
}

void FByVSoftObjectPath::SetPath(FName Path)
{
	SoftObjectPath.SetPath(Path);
}

UObject* FByVSoftObjectPath::TryLoad(FUObjectSerializeContext* InLoadContext) const
{
	return SoftObjectPath.TryLoad(InLoadContext);
}

UObject* FByVSoftObjectPath::ResolveObject() const
{
	return SoftObjectPath.ResolveObject();
}

bool FByVSoftObjectPath::Serialize(FArchive& Ar)
{
	return SoftObjectPath.Serialize(Ar);
}

bool FByVSoftObjectPath::Serialize(FStructuredArchive::FSlot Slot)
{
	return SoftObjectPath.Serialize(Slot);
}

bool FByVSoftObjectPath::operator==(FByVSoftObjectPath const& Other) const
{
	return SoftObjectPath == Other.SoftObjectPath;
}

bool FByVSoftObjectPath::ExportTextItem(FString& ValueStr, FByVSoftObjectPath const& DefaultValue, UObject* Parent,
	int32 PortFlags, UObject* ExportRootScope) const
{
	return SoftObjectPath.ExportTextItem(ValueStr, DefaultValue.SoftObjectPath, Parent, PortFlags, ExportRootScope);
}

bool FByVSoftObjectPath::ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent,
	FOutputDevice* ErrorText, FArchive* InSerializingArchive)
{
	return SoftObjectPath.ImportTextItem(Buffer, PortFlags, Parent, ErrorText, InSerializingArchive);
}

bool FByVSoftObjectPath::SerializeFromMismatchedTag(FPropertyTag const& Tag, FStructuredArchive::FSlot Slot)
{
	return SoftObjectPath.SerializeFromMismatchedTag(Tag, Slot);
}

void FByVSoftObjectPath::SerializePath(FArchive& Ar)
{
	SoftObjectPath.SerializePath(Ar);
}

bool FByVSoftObjectPath::PreSavePath(bool* bReportSoftObjectPathRedirects)
{
	return SoftObjectPath.PreSavePath(bReportSoftObjectPathRedirects);
}

void FByVSoftObjectPath::PostLoadPath(FArchive* InArchive) const
{
	SoftObjectPath.PostLoadPath(InArchive);
}

bool FByVSoftObjectPath::FixupForPIE()
{
	return SoftObjectPath.FixupForPIE();
}

bool FByVSoftObjectPath::FixupForPIE(int32 PIEInstance)
{
	return SoftObjectPath.FixupForPIE(PIEInstance);
}

bool FByVSoftObjectPath::FixupCoreRedirects()
{
	return SoftObjectPath.FixupCoreRedirects();
}

FByVSoftObjectPath FByVSoftObjectPath::GetOrCreateIDForObject(const UObject* Object)
{
	check(Object);
	return FByVSoftObjectPath(Object);
}

void FByVSoftObjectPath::AddPIEPackageName(FName NewPIEPackageName)
{
	FSoftObjectPath::AddPIEPackageName(NewPIEPackageName);
}

void FByVSoftObjectPath::ClearPIEPackageNames()
{
	FSoftObjectPath::ClearPIEPackageNames();
}
