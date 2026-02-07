# 项目目录结构说明

本文档定义工装测试项目的标准目录结构，适用于水表、气表、膜表及多元产品的测试工装项目。

## 目录总览

```
{project-name}/
├── README.md                   # 项目概述、快速上手
├── VERSION                     # 版本号，与 git tag 保持一致
├── CHANGELOG.md                # 版本变更记录
├── RELEASE_CHECKLIST.md        # 发布检查清单
├── .gitignore
├── .gitattributes              # Git LFS 配置
│
├── docs/                       # 文档
│   ├── protocols/              # 通信协议
│   ├── specs/                  # 规格需求
│   ├── guides/                 # 操作指南
│   └── notes/                  # 会议记录、沟通备忘（可选）
│
├── hardware/                   # 硬件相关
│   ├── reference/              # 硬件工程师提供的参考资料
│   ├── tester/                 # 测试板（你绘制的）
│   └── bom/                    # 物料清单
│
├── firmware/                   # 固件
│   ├── src/                    # 源码（如果提供）
│   └── docs/                   # 固件相关文档
│
├── software/                   # 上位机程序（Python）
│   ├── src/                    # 源代码
│   ├── config/                 # 配置文件
│   ├── scripts/                # 辅助脚本
│   └── tests/                  # 单元测试（可选）
│
├── samples/                    # 样本数据
│
├── tools/                      # 第三方工具、烧录配置等
│
└── .vscode/                    # VSCode 工作区配置
```

---

## 各目录详细说明

### /docs - 文档目录

```
docs/
├── protocols/                  # 通信协议文档
│   ├── mcu-protocol.md         # 与被测设备/嵌软的通信协议
│   ├── mes-protocol.md         # 与 MES 系统的通信协议
│   └── module-protocol.md      # 通信模块协议（LoRaWAN/NB-IoT 等）
│
├── specs/                      # 规格需求文档
│   ├── requirements.md         # 测试需求、功能要求
│   ├── test-items.md           # 测试项清单
│   └── acceptance.md           # 验收标准
│
├── guides/                     # 操作指南
│   ├── test-flow.md            # 整体测试流程
│   ├── test-steps.md           # 工装操作步骤详解
│   ├── deployment.md           # 部署上线指南
│   └── troubleshooting.md      # 常见问题排查
│
└── notes/                      # 备忘（可选）
    └── 2024-12-meeting.md      # 与硬件/嵌软的沟通记录
```

**文件命名规则：** 小写字母，单词用 `-` 连接，`.md` 格式。

---

### /hardware - 硬件目录

```
hardware/
├── reference/                  # 硬件工程师提供的参考文件
│   ├── sch/                    # 原理图
│   │   └── v1.0/
│   │       └── MainBoard.SchDoc
│   ├── pcb/                    # PCB 文件
│   │   └── v1.0/
│   └── docs/                   # 硬件相关文档
│       ├── datasheet/          # 芯片手册
│       └── hardware-spec.pdf   # 硬件规格书
│
├── tester/                     # 测试工装板（你绘制的）
│   ├── sch/                    # 原理图源文件
│   │   └── v1.0/
│   ├── pcb/                    # PCB 源文件
│   │   └── v1.0/
│   ├── gerber/                 # Gerber 打样文件（.gitignore，放 Release）
│   ├── 3d/                     # 3D 模型（如有外壳）
│   └── docs/                   # 测试板相关说明
│       └── io-mapping.md       # 引脚分配说明
│
└── bom/                        # 物料清单
    ├── bom-tester-v1.0.xlsx
    └── bom-tester-v1.1.xlsx
```

**硬件文件版本管理：**
- 用 `v1.0/`、`v1.1/` 子目录区分大版本
- 小改动在同一目录内，靠 git 历史追溯
- Gerber 打样文件不入库，打包后上传到 GitHub Release

---

### /firmware - 固件目录

```
firmware/
├── src/                        # 固件源码（如果嵌软提供）
│   └── bootloader/
│
├── docs/                       # 固件相关文档
│   ├── flash-map.md            # Flash 分区说明
│   ├── boot-protocol.md        # Bootloader 协议
│   └── upgrade-guide.md        # 升级流程
│
└── tools/                      # 烧录相关
    └── pyocd/
        └── target.yaml         # PyOCD 目标配置
```

**说明：**
- `.bin`、`.hex` 等固件二进制文件不入库，放 GitHub Release
- 如需版本对应，在 Release 附件中注明固件版本

---

### /software - 上位机程序目录

```
software/
├── src/                        # 源代码
│   ├── main.py                 # 程序入口
│   ├── core/                   # 核心逻辑
│   │   ├── tester.py           # 测试主流程
│   │   ├── protocol.py         # 通信协议解析
│   │   └── mes.py              # MES 对接
│   ├── drivers/                # 驱动层
│   │   ├── serial_port.py
│   │   └── power_supply.py
│   ├── ui/                     # 界面（如有）
│   └── utils/                  # 工具函数
│       ├── logger.py
│       └── config.py
│
├── config/                     # 配置文件
│   ├── default.yaml            # 默认配置
│   ├── config.debug.yaml       # Debug 模式覆盖配置
│   └── products/               # 不同产品/地区的配置
│       ├── MY-lorawan.yaml     # 马来 LoRaWAN 配置
│       └── CN-nbiot.yaml       # 国内 NB-IoT 配置
│
├── scripts/                    # 辅助脚本
│   ├── parse_log.py            # 日志分析
│   ├── generate_report.py      # 生成报告
│   └── batch_test.py           # 批量测试
│
├── tests/                      # 单元测试（可选）
│   └── test_protocol.py
│
├── requirements.txt            # Python 依赖
├── setup.py                    # 打包配置（可选）
└── README.md                   # 软件部分说明
```

**Debug vs Release 处理方式：**
- 不分两个文件夹，用配置 + 命令行参数区分
- `python main.py` → Release 模式
- `python main.py --debug` → Debug 模式
- VSCode 的 `launch.json` 配置两种启动方式

---

### /samples - 样本数据目录

```
samples/
├── test-logs/                  # 测试日志样本
│   ├── pass-sample.log
│   └── fail-sample.log
├── protocol-captures/          # 协议抓包数据
└── mes-responses/              # MES 返回样本
```

**用途：**
- 调试和开发时使用的参考数据
- 新人熟悉系统时的样例
- 单元测试的输入数据

---

### /tools - 第三方工具目录

```
tools/
├── pyocd/                      # 调试器配置
├── serial/                     # 串口工具配置
└── flash/                      # 烧录工具
```

---

### /.vscode - VSCode 配置

```
.vscode/
├── settings.json               # 编辑器设置
├── launch.json                 # 调试配置（Debug/Release）
├── tasks.json                  # 任务配置
└── extensions.json             # 推荐插件（可选）
```

---

## 根目录文件说明

| 文件 | 说明 |
|------|------|
| `README.md` | 项目概述、快速上手指南 |
| `VERSION` | 版本号，纯文本，如 `1.0.0`，与 git tag 一致 |
| `CHANGELOG.md` | 版本变更记录 |
| `RELEASE_CHECKLIST.md` | 发布时的检查清单、打包内容 |
| `.gitignore` | Git 忽略规则 |
| `.gitattributes` | Git LFS 配置 |

---

## 不入库的内容（放 GitHub Release）

以下内容通过 `.gitignore` 排除，发布时打包上传到 Release 附件：

| 类型 | 说明 |
|------|------|
| `hardware/tester/gerber/` | Gerber 打样文件包 |
| `firmware/*.bin` `*.hex` | 固件二进制 |
| 打包后的上位机程序 | 如 `.exe` 或打包的 Python |

**Release 附件命名建议：**
```
{project-name}-gerber-v1.0.0.zip
{project-name}-firmware-v1.0.0.bin
{project-name}-software-v1.0.0.zip
```

---

## 可选目录（按需添加）

| 目录 | 场景 |
|------|------|
| `docs/notes/` | 需要记录沟通过程 |
| `hardware/tester/3d/` | 有外壳或结构件 |
| `software/tests/` | 有单元测试需求 |
| `samples/` | 需要样本数据辅助开发 |
| `tools/` | 有第三方工具配置需要共享 |
