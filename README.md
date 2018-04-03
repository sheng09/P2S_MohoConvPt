P2S_MohoConvPt
==============

This program is for calculating the P-to-S conversion point for teleseimic earthquakes given layered model, and station associated coordinates.

- Author: Sheng Wang
- Contact: wangsheng.cas(at)gmail.com

# 1. How to install
```
make
make install
```
Then add the generated directory of `your path to bin/`  into your `PATH`.

# 2. Tools
- findConvPt

# 3. Examples
Find `run.sh` in `exam/`. `exam/test.mod` is the example model, and `exam/test.in` contains station associated coordinates.

# 4. DEV LOG
- Init for calculate the ray P-to-S conversion points at the Moho of teleseismic earthquake. (2018/03)
