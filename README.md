STM32 F4 Discovery Examples
===========================
```
http://openavproductions.com/stm32-f4-discovery
```
![screenshot](https://raw.github.com/harryhaaren/openAV-stm32f4/master/images/stm32f4discovery.jpg "The STM32 F4 Discovery board")

Intro
-----
This is a repository containing code examples that are introduced by the article
at the link above. Please read it, and you'll be able to get started with the
code quickly and understand the tools used in this repository.

These tutorials assume the device in use is a STM32 F4 Discovery (also referred
to as the STM32F407). This device is particularly useful for audio fanatics, as
it has an onboard audio-capable DAC, and a class D speaker driver.

See the section below on downloading the STM32 Firmware library - without doing
this step, you will not be able to build these example programs!

DSP and FPUs
------------
Inside the CPU there is a hardware Floating-Point-Unit(FPU), which allows us to 
do calculations with float variables pretty fast. Since almost all Digital 
Signal Processing(DSP) is done using floating point, its very useful to have a
hardware FPU.

Download the STM32 Firmware library
-----------------------------------
On this page, under the heading `Related Tools and Software` there is a link to
the current version of the F4 Discovery board firmware libraries. These are
needed to code using the peripheral devices available on the F4.
```
# Direct link (current at time of writing)
wget http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stsw-stm32136.zip
unzip stsw-stm32136.zip
```
The makefiles in each tutorial 0x_name set the include directory relative to the
code - if unzipped just as above, the examples will work - do *not* move or unzip
the firmware to another location - it will not work!

This is the official ST download page, see section `Related Tools and 
Software`, and download the `STM32F401 discovery firmware package`.
```
http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1848/PF259098?s_searchtype=partnumber
```

Contact
-------
If you have a particular question, you can email me. If you find these tutorials
useful, and want to support OpenAV in writing more tutorials like this, you could
do so at the link below.

Cheers, -Harry
```
harryhaaren@gmail.com
http://openavproductions.com/support
```
