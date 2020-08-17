#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Graph2.py
#  
#  Copyright 2019 shreyas <shreyas@shreyas-Inspiron-5570>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  
import numpy as np
import matplotlib.pyplot as plt

n = np.arange(25)



x = np.cos(2 * np.pi * 3 * 0.125 * n )

plt.xlabel('n')

plt.ylabel('x[n]')
plt.title(r'Plot of DT signal $x[n] =  \cos(2\pi [3/8] n )$ fo= 3kHz')

plt.stem(n, x)
plt.show()
