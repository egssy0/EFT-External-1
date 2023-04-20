#include <Windows.h>
#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <TlHelp32.h>
#include "DriverControl.h"

template <typename Type>
Type ReadChain(uint64_t address, std::vector<uint64_t> chain) {
	uint64_t current = address;
	for (int i = 0; i < chain.size() - 1; i++) {
		current = Driver.Read<uint64_t>(current + chain[i]);
	}
	return Driver.Read<Type>(current + chain[chain.size() - 1]);
}

template <typename T>
std::vector<T> ReadVector(uintptr_t Va, int size)
{
	std::vector<T> TempData{};
	TempData.resize(sizeof(T) * size);
	if (Driver.ReadArrbool((PVOID)(Va), &TempData[0], sizeof(T) * size))
		return TempData;

	return TempData;
}

