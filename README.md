# Test branch
So you found my test branch.
Tis branch is for learning how to write kernel modules.

# I2C Tools tutorial
Tutorial on using the i2c tools on Archlinux.
First you neeed 2 pakages to get this to work.
'''
pacman -Syu i2c-tools lm_sensors
'''
Then we need to load the i2c module in to the kearnel
'''
modprobe i2c-dev
'''
Now the we can use i2cdectect to sceann the i2cbuss.
'''
sudo i2cdetect -y -r 9
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- 18 -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- 44 -- -- -- -- -- -- -- -- -- -- --
50: -- -- 52 -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --
'''
