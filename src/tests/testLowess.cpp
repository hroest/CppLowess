//
// Copyright (c) 2015, Hannes Roest
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <CppLowess/Lowess.h>

#include <vector>
#include <list>
#include <deque>
#include <iostream>
#include <assert.h>

/// Minimal implementation of a template
class TestContainer
{

  std::vector<double> data_;
/// Some other stuff may go here

public:

  typedef std::vector<double>::iterator iterator;

  TestContainer() {}
  explicit TestContainer(int n)
  {
    data_.resize(n);
  }

  inline size_t size() const
  {
    return data_.size();
  }

  inline double& operator[](size_t n)
  {
    return data_[n];
  }

  const inline double& operator[](size_t n) const
  {
    return data_[n];
  }

  inline void push_back(double x)
  {
    return data_.push_back(x);
  }

  inline std::vector<double>::iterator begin()
  {
    return data_.begin();
  }

  inline std::vector<double>::iterator end()
  {
    return data_.end();
  }

};

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

double xval[] = {1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 10, 12, 14, 50 };
double yval[] = { 18, 2, 15, 6, 10, 4, 16, 11, 7, 3, 14, 17, 20, 12, 9, 13, 1, 8, 5, 19};

double ys_1[] =
{
  13.659, 11.145, 8.701, 9.722, 10.000, 11.300, 11.300,
  11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 13.000,
  6.440, 5.596, 5.456, 18.998
};

double ys_2[] =
{
  13.659, 12.347, 11.034, 9.722, 10.511, 11.300, 11.300,
  11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 11.300, 13.000,
  6.440, 5.596, 5.456, 18.998
};

double ys_3[] =
{
  14.811, 12.115, 8.984, 9.676, 10.000, 11.346, 11.346,
  11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 11.346, 13.000,
  6.734, 5.744, 5.415, 18.998
};

int main()
{

  CppLowess::TemplatedLowess<std::vector<double>, double> dlowess;
  {
    std::vector<double> v_xval;
    std::vector<double> v_yval;
    for (size_t i = 0; i < 20; i++)
    {
      v_xval.push_back(xval[i]);
      v_yval.push_back(yval[i]);
    }

    // YS values with F = .25, NSTEPS = 0, DELTA = 0.0
    {
      std::vector<double> out(20), tmp1(20), tmp2(20);
      dlowess.lowess(v_xval, v_yval, 0.25, 0, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_1[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 0 ,  DELTA = 3.0
    {
      std::vector<double> out(20), tmp1(20), tmp2(20);
      dlowess.lowess(v_xval, v_yval, 0.25, 0, 3.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_2[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 2, DELTA = 0.0
    {
      std::vector<double> out(20), tmp1(20), tmp2(20);
      dlowess.lowess(v_xval, v_yval, 0.25, 2, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_3[i]) / out[i] < 1e-4);
      }
    }
  }

  CppLowess::TemplatedLowess<std::vector<float>, float>  flowess;
  {
    std::vector<float> v_xval;
    std::vector<float> v_yval;
    for (size_t i = 0; i < 20; i++)
    {
      v_xval.push_back((float)xval[i]);
      v_yval.push_back((float)yval[i]);
    }

    // YS values with F = .25, NSTEPS = 0, DELTA = 0.0
    {
      std::vector<float> out(20), tmp1(20), tmp2(20);
      flowess.lowess(v_xval, v_yval, 0.25, 0, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_1[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 0 ,  DELTA = 3.0
    {
      std::vector<float> out(20), tmp1(20), tmp2(20);
      flowess.lowess(v_xval, v_yval, 0.25, 0, 3.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_2[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 2, DELTA = 0.0
    {
      std::vector<float> out(20), tmp1(20), tmp2(20);
      flowess.lowess(v_xval, v_yval, 0.25, 2, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_3[i]) / out[i] < 1e-4);
      }
    }
  }

  CppLowess::TemplatedLowess<TestContainer, double> testlowess;
  {

    TestContainer v_xval;
    TestContainer v_yval;
    for (size_t i = 0; i < 20; i++)
    {
      v_xval.push_back(xval[i]);
      v_yval.push_back(yval[i]);
    }


    // YS values with F = .25, NSTEPS = 0, DELTA = 0.0
    {
      TestContainer out(20), tmp1(20), tmp2(20);
      testlowess.lowess(v_xval, v_yval, 0.25, 0, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_1[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 0 ,  DELTA = 3.0
    {
      TestContainer out(20), tmp1(20), tmp2(20);
      testlowess.lowess(v_xval, v_yval, 0.25, 0, 3.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_2[i]) / out[i] < 1e-4);
      }
    }

    // YS values with F = .25, NSTEPS = 2, DELTA = 0.0
    {
      TestContainer out(20), tmp1(20), tmp2(20);
      testlowess.lowess(v_xval, v_yval, 0.25, 2, 0.0, out, tmp1, tmp2);
      for (size_t i = 0; i < 20; i++)
      {
        assert(fabs(out[i] - ys_3[i]) / out[i] < 1e-4);
      }
    }
  }

  std::cout << "All tests ran successfully" << std::endl;

}
