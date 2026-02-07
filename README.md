# {项目名称}

> {一句话描述这个项目}

## 概述

- **产品类型**：{水表/气表/膜表/...}
- **计量方式**：{超声波/霍尔/...}
- **通信方式**：{LoRaWAN/NB-IoT/...}
- **目标地区**：{马来/国内/...}
- **当前版本**：见 [VERSION](./VERSION)

## 目录结构

```
├── docs/           # 文档（协议、流程、操作指南）
├── hardware/       # 硬件（参考资料、测试板）
├── firmware/       # 固件（源码、文档）
├── software/       # 上位机程序
├── samples/        # 样本数据
└── tools/          # 第三方工具
```

详见 [PROJECT_STRUCTURE.md](./PROJECT_STRUCTURE.md)

## 快速开始

### 环境要求

- Python 3.10+
- PyOCD（调试器）
- {其他依赖}

### 安装

```bash
cd software
pip install -r requirements.txt
```

### 运行

```bash
# Release 模式
python src/main.py

# Debug 模式
python src/main.py --debug
```

### 配置

1. 复制配置模板：
   ```bash
   cp config/default.yaml config/local.yaml
   ```
2. 修改 `config/local.yaml` 中的串口、MES 地址等参数

## 测试流程

详见 [docs/guides/test-flow.md](./docs/guides/test-flow.md)

## 文档索引

| 文档 | 说明 |
|------|------|
| [test-flow.md](./docs/guides/test-flow.md) | 测试流程 |
| [test-steps.md](./docs/guides/test-steps.md) | 操作步骤 |
| [protocol-mcu.md](./docs/protocols/protocol-mcu.md) | MCU 通信协议 |
| [protocol-mes.md](./docs/protocols/protocol-mes.md) | MES 通信协议 |
| [troubleshooting.md](./docs/guides/troubleshooting.md) | 故障排查 |

## 版本历史

见 [CHANGELOG.md](./CHANGELOG.md)

## Release 附件

每个 Release 包含：
- `{项目名}-gerber-vX.X.X.zip` - Gerber 打样文件
- `{项目名}-firmware-vX.X.X.bin` - 固件（如有）
- `{项目名}-software-vX.X.X.zip` - 上位机程序包

## 相关项目

- [{硬件工程师的仓库}]()
- [{嵌软的仓库}]()

## 维护者

- {你的名字} - 测试工装开发

---

*Last updated: {日期}*
