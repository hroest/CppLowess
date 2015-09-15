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

from libcpp.vector cimport vector as libcpp_vector
from cython.operator cimport dereference as deref, preincrement as inc, address as address

cdef extern from "Lowess.h" namespace "CppLowess":

    cdef cppclass TemplatedLowess[ContainerType, ValueType]:

        TemplatedLowess() nogil except +
        int lowess(ContainerType& x,
                   ContainerType& y,
                   double frac,
                   int nsteps, 
                   ValueType delta,
                   ContainerType& ys,
                   ContainerType& resid_weights,
                   ContainerType& weights
                  )



def lowess(x, y, double frac, int nsteps, double delta):
    cdef size_t dataSize = len(x)
    cdef libcpp_vector[double] c_x = x
    cdef libcpp_vector[double] c_y = y

    cdef libcpp_vector[double] resid_weights
    cdef libcpp_vector[double] weights
    cdef libcpp_vector[double] result

    resid_weights.resize(dataSize)
    weights.resize(dataSize)
    result.resize(dataSize)

    cdef TemplatedLowess[ libcpp_vector[double], double] algo
    algo.lowess(c_x, c_y, frac, nsteps, delta, result, resid_weights, weights)

    return result

