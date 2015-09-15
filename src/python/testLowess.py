"""
Copyright (c) 2015, Hannes Roest

This software is released under a three-clause BSD license:
 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of any author or any participating institution
   may be used to endorse or promote products derived from this software
   without specific prior written permission.
For a full list of authors, refer to the file AUTHORS.
--------------------------------------------------------------------------
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""

import PyLowess
import unittest


"""
/*
*        X values:
*          1  2  3  4  5  (10)6  8  10  12  14  50
* 
*        Y values:
*           18  2  15  6  10  4  16  11  7  3  14  17  20  12  9  13  1  8  5  19
* 
* 
*        YS values with F = .25, NSTEPS = 0, DELTA = 0.0
*         13.659  11.145  8.701  9.722  10.000  (10)11.300  13.000  6.440  5.596
*           5.456  18.998
* 
*        YS values with F = .25, NSTEPS = 0 ,  DELTA = 3.0
*          13.659  12.347  11.034  9.722  10.511  (10)11.300  13.000  6.440  5.596
*            5.456  18.998
* 
*        YS values with F = .25, NSTEPS = 2, DELTA = 0.0
*          14.811  12.115  8.984  9.676  10.000  (10)11.346  13.000  6.734  5.744
*            5.415  18.998
*/
"""

xval = [1, 2, 3, 4, 5, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 8, 10, 12, 14, 50 ];
yval = [ 18, 2, 15, 6, 10, 4, 16, 11, 7, 3, 14, 17, 20, 12, 9, 13, 1, 8, 5, 19];

ys_1 = [  13.659, 11.145, 8.701, 9.722, 10.000, 11.300, 11.300,
  11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 13.000,
  6.440, 5.596, 5.456, 18.998 ];

ys_2 = [ 13.659, 12.347, 11.034, 9.722, 10.511, 11.300, 11.300,
  11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 13.000,
  6.440, 5.596, 5.456, 18.998 ];

ys_3 = [ 14.811, 12.115, 8.984, 9.676, 10.000, 11.346, 11.346,
  11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 13.000,
  6.734, 5.744, 5.415, 18.998 ];

class TestMSNumpress(unittest.TestCase):

    def setUp(self):
        pass

    def test_1(self):
        """
        Original Fortran test 1

        YS values with F = .25, NSTEPS = 0, DELTA = 0.0
        """

        out = PyLowess.lowess(xval, yval, 0.25, 0, 0.0)
        for a,b in zip(ys_1, out):
            self.assertAlmostEqual(a,b, 3)

    def test_2(self):
        """
        Original Fortran test 2

        YS values with F = .25, NSTEPS = 0 ,  DELTA = 3.0
        """

        out = PyLowess.lowess(xval, yval, 0.25, 0, 3.0)
        for a,b in zip(ys_2, out):
            self.assertAlmostEqual(a,b, 3)

    def test_3(self):
        """
        Original Fortran test 3

        YS values with F = .25, NSTEPS = 2, DELTA = 0.0
        """

        out = PyLowess.lowess(xval, yval, 0.25, 2, 0.0)
        for a,b in zip(ys_3, out):
            self.assertAlmostEqual(a,b, 3)

