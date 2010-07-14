#include "KernelSystemEntry.h"

using namespace mge;

KernelSystemEntry::KernelSystemEntry(KernelSystem *sys, short weight) : sys(sys), weight(weight) { }

bool KernelSystemEntry::operator==(const KernelSystemEntry &entry) const {
	return (weight == entry.weight && sys == entry.sys);
}

bool KernelSystemEntry::operator<(const KernelSystemEntry &entry) const {
	return weight < entry.weight;
}


