# XGOllamaLink
Plugin Version:1.0
- [XGOllamaLink](#xgollamalink)
  - [Brief](#brief)
  - [Code base introduction](#code-base-introduction)
    - [Folder DocumentPictures:](#folder-documentpictures)
    - [Folder XGDeepSeekDemo:](#folder-xgdeepseekdemo)
  - [Use process](#use-process)
    - [1. Check that local Ollama and models are running properly](#1-check-that-local-ollama-and-models-are-running-properly)
    - [2. Use the Blueprint node for access](#2-use-the-blueprint-node-for-access)
      - [Generate](#generate)
      - [Version](#version)
  - [联系方式](#联系方式)

## Brief
Connect the engine plug-in to Unreal Engine 5 and Ollma</br>
English document:</br>
[English Instruction](./README.md)</br>
中文文档:</br>
[Chinese Instruction](./README_CN.md)</br>
Mall link:</br>
TODO </br>
Note:</br>
1.You need to deploy Ollama locally</br>
2.You need to download the model you want to access</br>
3.This plugin was developed by Huagang Liu, does not contain any code other than Unreal Engine code, does not store your application information, etc</br>
## Code base introduction
### Folder DocumentPictures:  

Various pictures in the document

### Folder XGDeepSeekDemo:
UE_5.3 development example project</br>
It requires a UEC++ development environment on the computer to work normally</br>
## Use process
### 1. Check that local Ollama and models are running properly
You should deploy Ollama on your local server and have normal access to conversations.</br>
Here is a demonstration from the command line on Windows:
```
ollama run deepseek-r1:1.5b
```

![image](DocumentPictures/001_CMD.png)  

### 2. Use the Blueprint node for access

#### Generate
![image](DocumentPictures/002_Generate.png)  
#### Version
![image](DocumentPictures/003_Version.png)  
## 联系方式

If you have any questions about XGOllamaLink plug-in products, please contact me.

QQ:
709777172  

Email:
709777172@qq.com  

bilibili:
[虚幻小刚](https://space.bilibili.com/8383085)  