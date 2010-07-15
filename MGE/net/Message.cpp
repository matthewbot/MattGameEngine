#include "Message.h"
#include <MGE/util/Exception.h>

using namespace mge;
using namespace std;

Message::Message() : channel(-1) { }
Message::Message(const Blob &d, int chan, Type t) : data(d), channel(chan), type(t) { }
