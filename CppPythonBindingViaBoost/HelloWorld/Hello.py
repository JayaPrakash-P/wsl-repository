#!/usr/bin/env python3

from hello import *

f = Foo(3)

b1 = f.get_bar()
b2 = f.get_bar()

b1x = b1.get_x()
b2x = b2.get_x()

print("b1x = ", b1x)
print("b2x = ", b2x)

b1.set_x(42)
b2.get_x()
b1x = b1.get_x()
b2x = b2.get_x()

print("b1x = ", b1x)
print("b2x = ", b2x)