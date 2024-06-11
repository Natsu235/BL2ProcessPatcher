#pragma once

#ifndef MEMORYSIGNATURE_H
#define MEMORYSIGNATURE_H

struct MemorySignature
{
	const char* Pattern;
	const char* Mask;
	int Position;
};

#endif