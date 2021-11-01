# Introduction
This repo attempts to implement custom floating point formats published by tesla
here https://tesla-cdn.thron.com/static/SBY4B9_tesla-dojo-technology_OPNZ0M.pdf

Central idea to this whitepaper is the ability to change the bias of floating point format. This allows them to represent different ranges of exponents with same number of bits. For example CFloat8_143 can represent $+/-[2^{1}, 1.111*2^{15}]$ with a bias of 0 and $+/-[2^{-30}, 1.111*2^{-16}]$ with a bias of 31. Bias is stored separately as a 6-bit number.

This scheme is particularly handy when we need different range of exponents for activations vs weight updates in neural networks.