# 2D's 3D Game

> 一款控制台2D地图探险游戏

项目使用[GNU Lesser General Public License v3](LICENSE)，项目中任何文件和代码、头文件（不包括7-Zip发行版）均采用此许可证，仅在此提示，恕不在代码中标识。

项目使用了7-Zip Extra的编译后版本：

```
7-Zip Extra is package of extra modules of 7-Zip.
7-Zip Copyright (C) 1999-2024 Igor Pavlov.
7-Zip is free software. Read License.txt for more information about license.
Source code of binaries can be found at:
http://www.7-zip.org/
```
```
  7-Zip Extra
  ~~~~~~~~~~~
  License for use and distribution
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  Copyright (C) 1999-2024 Igor Pavlov.

  7-Zip Copyright (C) 1999-2024 Igor Pavlov.

  The licenses for files are:

    - 7za.exe:
         - The "GNU LGPL" as main license for most of the code
         - The "BSD 3-clause License" for some code
         - The "BSD 2-clause License" for some code
    - All other files: the "GNU LGPL".

  Redistributions in binary form must reproduce related license information from this file.

  Note: 
        You can use 7-Zip Extra on any computer, including a computer in a commercial 
        organization. You don't need to register or pay for 7-Zip.

  It is allowed to digitally sign DLL and EXE files included into this package
  with arbitrary signatures of third parties.


GNU LGPL information
--------------------

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You can receive a copy of the GNU Lesser General Public License from
    http://www.gnu.org/



BSD 3-clause License in 7-Zip code
----------------------------------

  The "BSD 3-clause License" is used for the following code in 7za.exe
    -  ZSTD data decompression.
       that code was developed using original zstd decoder code as reference code.
       The original zstd decoder code was developed by Facebook Inc,
       that also uses the "BSD 3-clause License".

  Copyright (c) Facebook, Inc. All rights reserved.
  Copyright (c) 2023-2024 Igor Pavlov.

Text of the "BSD 3-clause License"
----------------------------------

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

---




BSD 2-clause License in 7-Zip code
----------------------------------

  The "BSD 2-clause License" is used for the XXH64 code in 7za.exe.

  XXH64 code in 7-Zip was derived from the original XXH64 code developed by Yann Collet.

  Copyright (c) 2012-2021 Yann Collet.
  Copyright (c) 2023-2024 Igor Pavlov.

Text of the "BSD 2-clause License"
----------------------------------

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

---
```

## 重要提示

2025-8-9 2D's 3D Game社区服务器暂未启动，文档中关于服务器的内容皆为拟定内容，不代表实际情况。

本项目所有程序都要求读取的文件为ANSI编码，否则会乱码，请确认每一个id和地图文件均为ANSI编码！

## 介绍

从社区下载地图，在游戏内导入，设置玩法，游玩。就是这么简单！

2D's 3D Game有娱乐模式和竞速模式，两种模式各有特色功能和玩法，您可以自己探索。

```
玩法

这是一个用二维的矩阵来玩三维的地图的游戏。三维地图由正方体格子组成,在二维地图中只有高度来表示。

在二维地图中,有两种走法。
示例地图
（以下地图并不是格子高度,而是位置标号）
[1] [2] [3]
[4] [5] [6]
[7] [8] [9]

1. ↑↓←→
如果在[5]的位置,↑↓←→即为到[2],[8],[4],[6]。
记录原格子高度为a,目标格子高度为b,只有在
b-a={-2, -1, 0, 1}
时可以↑↓←→移动。

2. ↖↗↙↘
如果在[5]的位置,↖↗↙↘即为到[1],[3],[7],[9]。
记录原格子高度为a,目标格子高度为b,只有在满足条件A时可以↑↓←→移动。
示例地图
（以下地图是格子高度）
a c
d b
如果要在这样一个2×2的地图中进行↖↗↙↘,例如从a到b。
条件A:b-a={-2, -1, 0},且a≥c或a≥d。
```

自研简易地图加密算法：对于地图的每一个格子数值，用密码字符串的SHA-256的每一位和它进行异或运算。

## 安装与使用

1. 下载release版游戏文件。
1. 运行`+set.exe`，快速创建ID文件和设置玩家的话。（从VeryLow移植）
1. 从社区下载地图，存放到`/map`文件夹，或者直接复制。
1. 运行游戏`2D's 3D Game-Community.exe`，开始游玩。
1. 如果想要将娱乐地图格式化为竞速地图，运行`mapformart.exe`即可。

## 账号机制

> 考虑到普通游戏玩家并不会对2D's 3D Game感兴趣，以下内容仅供资深计算机爱好者阅读。

2D's 3D Game的账号并不是存储在服务器，而是本地的一个凭证，这就免去了绑定自身社交账号或手机号的操作。

账号的唯一凭证便是一份txt文件，这个规则在任何2D's 3D Game社区使用了账号的情况下都使用，如游戏、地图上传、排名等。为了证明您的身份，千万不要把凭证传输给他人。如果多人合用一个账号，是允许的。

这个凭证txt文件本质上和激活密钥或卡密没有区别，都是一串唯一的字符，用于证明自己唯一的身份——自己手输一串字符或用生成器生成字符作为凭证都是允许的，但我们建议您使用VeryLow-2D's 3D Game定制版（游戏发行文件内已附带为+set.exe）。

为了安全，2D's 3D Game仅支持小于`100000B`、仅包含ASCII字符的文本文件的凭证，如果不遵守此规则，后果自负，包括但不仅限于不承认您的成绩。

## 账号申请

由于账号的凭证非常容易生成，会导致账号繁多，在我们的服务器中上传地图或成绩排名时仅支持注册账号。

### 如何获得注册账号？

1. 前往申请页面上传你的账号凭证（id文件），我们只存储您账号的哈希校验值和您的IP，然后得到验证码。一个IP只允许注册一个账号。

2. 向`34067513@qq.com`发一封申请账号的邮件，包含以下内容：

   ```
   正文
   -您的IP - 申请页面上传账号凭证时会显示
   -您的验证码 - 申请页面上传账号凭证时会显示
   -您要申请的用户名 - 仅允许A-Za-z0-9_
   -您的头像图片的URL链接 - 可以使用第三方图床，我们的服务器不存储头像图片
   -您的计算机名 - 用于辅助验证您的通关报告属于您，可以多个
   -您的个人简介
   
   附件
   -录屏视频，中间不间断，内容为使用7-zip对您的账号凭证id文件进行SHA-256校验，并展示校验结果
   -id文件加密压缩包
   
   注释：录屏视频中的SHA-256校验用于证明您的账号和1.中的一致；您发送的id文件加密压缩包仅用于将来你丢失id文件后找回时使用，密码自定，人人都可用您的用户名或id hash下载这个id文件加密压缩包，但只有你知道这个压缩包的密码。
   ```

4. 等待PerryDing的审核，即可使用账号，本地游玩时加载这个id文件即可。如果需要更新信息，再按2.发送邮件即可。

## 用户协议（社区公平性与身份验证条款）

> 使用2D's 3D Game社区的任意服务，包括但不仅限于使用2D's 3D Game的服务器、使用账号、地图上传、排名等，即表示您同意本用户协议。

### 1. 社区公平性原则

2D's 3D Game作为IQ Online Studio开发的开源游戏，致力于构建公平、透明、方便的游玩社区。由于开源特性允许任何人编译、修改游戏代码，为确保竞技公平性与身份真实性，我们建立以下验证机制。

### 2. 认证版本说明

为证明您的玩家身份及无作弊行为，建议使用2D's 3D Game IQ Online Studio官方版本**或**IQ Online Studio官方认证的衍生/分支版本**进行游戏。此类版本具备以下特性：

*   游戏结束后自动生成包含唯一哈希校验值的通关报告

*   哈希值与报告内容绑定，可验证报告未被篡改

*   支持社区内的成绩互认、自证，与公平竞技对比

### 3. 通关报告内容说明

认证版本生成的通关报告为压缩包形式，包含以下几类信息，用于验证游戏过程真实性（如果有疑问，欢迎翻阅源代码）：
```
基础信息（/readme）
-游戏程序简介
-玩家的话（playerswords.txt）

玩家信息（/player）
-id文件哈希值（useridhash.txt，非明文账号凭证）
-计算机名称（computerName.txt，本地计算机名称）

通关报告（/result）
-通关详情报告（result.txt，含胜负状态、用时等核心数据）

地图数据（/map）
-原始地图文件哈希值（mapFileHash.txt）
-原始地图文件（mapOriginalFile.txt）
-内存中地图（可能已经修改）纯码（mapRAMOHash.txt）
-内存中原地图读取时纯码（mapRAMOriginal.txt）
-内存中通关时地图（mapRAMNow.txt）
-地图的话（mapswords.txt）

操作记录（/keyboard）
-游戏内有效输入（winRoadA.txt，影响游戏结果的关键输入）
-游戏内全部输入（winRoad.txt，包含所有按键时序）

系统与环境信息（/info）
-进程列表（tasklistV.txt、tasklistM.txt，用于检测异常程序）
-游戏目录文件结构（gameFolderFileList.txt，验证游戏文件完整性）
-游戏程序路径、哈希值（gamepath.txt，gamehash.txt，验证游戏文件）
-7-zip程序哈希值（7za.dll-hash.txt，7za.exe-hash.txt，7zxa.dll-hash.txt）
-硬件配置信息（CPU、内存、显卡等，以wmic开头的系列文件）
-系统信息（systeminfo.txt，操作系统版本、BIOS、网络配置等）
```


### 4. 未作弊证明方式

若您希望在社区中证明自己的成绩真实有效，可通过以下方式：

1.  **发布全程录屏**：录制完整游戏过程，确保通关时展示通关报告的所有内容，通关报告文件的哈希校验值清晰可见（不得遮挡）。

2.  **选择性公开报告**：可自愿选择是否公开通关报告压缩包（报告中含设备标识等私人信息，您有权决定公开范围）。

通过哈希校验与录屏的双重验证，社区可确认您确实并未篡改游戏文件、使用作弊工具等。

附：游戏使用的文件及其哈希SHA-256校验值正常值记录（实时更新）

*哈希校验值符合此记录的（单个文件符合对应的其中一个哈希值即可），可以排除通过修改这些文件来作弊的嫌疑。*

```
7za.dll:
bba4fd66795a5d5f7b32994f445fed03279750d7cf4973b589a01d9db42b3b31

7za.exe:
fbb3dadcc29bcbc5460484d858c5f33f99e5317f5f6cd8d9c83f4dd8c39b3e30

7zxa.dll:
bca6c849fe85adea595add66f12dc6285a6404b1451c336669089201a3107c84

游戏程序本体:
(v4.2)
ec29357be31c579fa9cf70a188c7bf44ca035fec1b14da71e83450b99f8bde1f
```

### 5. 隐私保护说明

*   通关报告中包含的设备信息、系统配置等属于个人敏感信息，**您完全拥有决定是否公开的自主权**。

*   IQ Online Studio不会强制收集或存储任何玩家的通关报告内容，所有报告均仅存储于您的本地设备。

### 6. 开源与修改说明

基于LGPL-v3协议，您可自由修改、分发游戏代码，但非官方认证的版本生成的报告将默认不被社区认可。若您发布修改后的衍生版本，建议在说明中明确标注与官方版本的差异，以保障社区信息透明。您可以联系IQ Online Studio，为您的分支/衍生申请认证。

我们相信，通过透明的验证机制与社区共同监督，能让2D's 3D Game成为更公平、更有趣的游戏社区。

> （注：文档部分内容可能由 AI 生成）
有事没事请加QQ群：743278470，你可以添加句子，报告错误，寻求帮助
