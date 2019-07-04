# Interesting development tools

In this section of our tutorial we will discuss several tips to help our development of multimedia applications. If you want to leap straight into FFmpeg move to the
third lesson. Otherwise, feel free to select the tool you want to learn in the menu below.

1. ffplay
2. ffprobe
3. netcat
4. lsof
5. GDB / LLDB
6. Python

## ffplay

ffplay is a simple yet very powerful command line player that can be compiled with FFmpeg. With ffplay you can test if your video / audio streamer is working properly, it supports
a incredible variety of network protocols such as: TCP, UDP, HTTP, RTP, transport streams such as MPEG-TS and the vast majority of video and audio codecs. ffplay can reproduce
anything you can imagine and is my go to player to test streams of audio and video, during the third lesson we will be using ffplay to test our streamer.

## ffprobe

ffprobe is another tool that comes shipped with FFmpeg. As the name says it is a prober that tells you a bunch of information about your file content. Sometimes we grab a few video samples
and don't really know if the codec or the framerate is what our code expects, that's why it is interesting to check these informations in advance, that's when ffprobe comes in place, I grabbed
an output of ffprobe so you can have a look on the amount of information it gives you. For this particular input we can see that we use an MP4 container with one h.264 video stream with Full HD resolution
and an approximate 24 fps of frame rate, we can also see an AAC audio stream.

```sh
$ ffprobe video1_1.mp4 

ffprobe version N-93387-gdef18ac43b Copyright (c) 2007-2019 the FFmpeg developers
  built with gcc 7 (Ubuntu 7.3.0-27ubuntu1~18.04)
  configuration: --enable-libfreetype --enable-gpl --enable-libx264 --enable-libvpx --enable-shared --enable-ffplay
  libavutil      56. 26.100 / 56. 26.100
  libavcodec     58. 47.103 / 58. 47.103
  libavformat    58. 26.101 / 58. 26.101
  libavdevice    58.  6.101 / 58.  6.101
  libavfilter     7. 48.100 /  7. 48.100
  libswscale      5.  4.100 /  5.  4.100
  libswresample   3.  4.100 /  3.  4.100
  libpostproc    55.  4.100 / 55.  4.100
Input #0, mov,mp4,m4a,3gp,3g2,mj2, from 'video1_1.mp4':
  Metadata:
    major_brand     : mp42
    minor_version   : 0
    compatible_brands: mp42mp41
    creation_time   : 2018-11-22T08:40:44.000000Z
  Duration: 00:05:29.33, start: 0.000000, bitrate: 1414 kb/s
    Stream #0:0(eng): Video: h264 (Main) (avc1 / 0x31637661), yuv420p(tv, bt709), 1920x1080, 1090 kb/s, 23.98 fps, 23.98 tbr, 24k tbn, 47.95 tbc (default)
    Metadata:
      creation_time   : 2018-11-22T08:40:44.000000Z
      handler_name    : ?Mainconcept Video Media Handler
      encoder         : AVC Coding
    Stream #0:1(eng): Audio: aac (LC) (mp4a / 0x6134706D), 48000 Hz, stereo, fltp, 317 kb/s (default)
    Metadata:
      creation_time   : 2018-11-22T08:40:45.000000Z
      handler_name    : #Mainconcept MP4 Sound Media Handler
```

## netcat

Netcat is a UDP and TCP connection listener, sometimes we need to perform early test on network sockets, that's when netcat shines. Let's assume a hypothetical scenario, we are developing an embedded video
player for a chromecast like device, and there is a requirement that there should be an over IP remote control implementation that lets you play, pause and seek the content. If you
start the implementation from the server and want to test the remote control feature you would have to create an application that mimics the, for example, mobile application that will be used as the 
remote. With netcat you can abstract the entire application and connect directly to that socket sending any information you want over a connection. You can send simple text command, files, you can even
wait on a port simulating a server. Netcat is a must know utility for your developer swiss army knife.

## lsof

Sometimes we are using a port for our server and all of a sudden we cannot bind to this port. Sometimes this is a problem with your socket setup, you forgot to set the reuse for the address / port, or maybe
you are using a reserved port and the process assigned to it spawned or perhaps your code bugged and kept left in the port. lsof lets you look at all the open ports in your system and check what type
of network protocol is in use, who is using, for how long it's in use and many more information. With this simple tool you can verify why you are not properly binding your socket to the kernel. 

## GDB and LLDB

GDB and LLDB are two verify similar debugging tools for C++ and many other languages. It is important to learn how to use a debugger to find obscure segmentation faults or stack overflows. I find both of these easy to use, however, in certain ocasions, specially when there is a lot of parallelism in your application LLDB can be more user-friendly.

## Python

Python is an extremely important language, it is multi-purpose, can be easily extended with a variety of libraries and is very simple to grasp onto. Python is the ultimate tool for simple and fast automation, however when you need performance you can't count on it every time. Yet python will be your go to language when trying to validate a solution. Maybe you are trying to test UDP multicast messages and are thinking of using netcat for it, I am sorry to inform you but that's
out of netcat scope, implementing a C code for such a simple test may be an overkill, that's when your Python knowledge will pay off, your implementation will be cut in half the amount of lines, you will be able to implement it quickly, with a lot of support from the community and will be able to perform changes without cracking your head. That's why Python is a must learn sripting language. 
