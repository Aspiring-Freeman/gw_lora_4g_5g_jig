# 命名规则详细说明

本文档定义工装测试项目的统一命名规则，确保项目、文件、代码的命名一致性和可追溯性。

---

## 一、项目（仓库）命名规则

### 1.1 命名格式

```
{产品类型}-{计量方式}-{通信方式}-{地区}-{工装类型}-jig
```

**各字段可选，按需组合，保持简洁。**

### 1.2 字段编码表

#### 产品类型 (Product Type)

| 编码 | 全称 | 说明 |
|------|------|------|
| `wm` | Water Meter | 水表 |
| `gm` | Gas Meter | 气表 |
| `dm` | Diaphragm Meter | 膜式燃气表（膜表） |
| `dv` | Diverse | 多元（杂项，无固定分类） |
| `cm` | Communication Module | 纯通信模块（非整机） |
| `pm` | Pressure Monitor | 压力监测 |
| `tm` | Thermal Meter | 热量表 |

#### 计量方式 (Measurement)

| 编码 | 全称 | 说明 |
|------|------|------|
| `us` | Ultrasonic | 超声波 |
| `hl` | Hall | 霍尔 |
| `mc` | Mechanical | 机械式 |
| `em` | Electromagnetic | 电磁式 |
| 空 | - | 不适用或不区分 |

#### 通信方式 (Communication)

| 编码 | 全称 | 说明 |
|------|------|------|
| `lora` | LoRaWAN | LoRaWAN 通信 |
| `nb` | NB-IoT | NB-IoT 通信 |
| `cat1` | Cat-1 | Cat-1 蜂窝通信 |
| `4g` | 4G LTE | 4G 通信 |
| `wifi` | WiFi | WiFi 通信 |
| `mbus` | M-Bus | M-Bus 总线 |
| `wired` | Wired | 有线（RS485/232 等） |
| 空 | - | 不涉及通信或不区分 |

#### 地区 (Region)

| 编码 | 说明 |
|------|------|
| `cn` | 中国大陆 |
| `my` | 马来西亚 |
| `eu` | 欧洲 |
| `sea` | 东南亚（泛指） |
| `intl` | 国际通用 |
| 空 | 不区分地区 |

#### 工装类型 (Jig Type)

| 编码 | 说明 |
|------|------|
| `func` | 功能测试工装 |
| `comm` | 通信测试工装 |
| `pcba` | PCBA 测试工装 |
| `aging` | 老化测试工装 |
| `cal` | 校准工装 |
| `prod` | 产线综合测试工装 |
| 空 | 通用/不细分 |

### 1.3 命名示例

| 项目 | 仓库名 | 说明 |
|------|--------|------|
| 马来 LoRaWAN 超声波水表产线测试 | `wm-us-lora-my-jig` | 完整字段 |
| 国内 NB-IoT 水表测试 | `wm-nb-cn-jig` | 省略计量方式 |
| 霍尔气表通用测试 | `gm-hl-jig` | 省略通信、地区 |
| 膜式燃气表 PCBA 测试 | `dm-pcba-jig` | 膜表 + 工装类型 |
| Cat-1 模块测试 | `cm-cat1-jig` | 纯通信模块 |
| LoRaWAN 模块测试 | `cm-lora-jig` | 纯通信模块 |
| 多元部门某项目 | `dv-xxx-jig` | xxx 自定义描述 |
| 压力监测设备测试 | `pm-nb-jig` | 压力监测 + NB |

### 1.4 多元项目命名

多元部门项目无固定规律，采用 `dv-{简短描述}-jig` 格式：

```
dv-valve-controller-jig      # 阀门控制器
dv-display-unit-jig          # 显示单元
dv-sensor-board-jig          # 传感器板
dv-customer-xxx-jig          # 特定客户项目
```

---

## 二、硬件文件命名规则

### 2.1 原理图/PCB 文件命名

```
{模块名}_{版本}.{扩展名}
```

| 示例 | 说明 |
|------|------|
| `MainBoard_v1.0.SchDoc` | 主板原理图 v1.0 |
| `MainBoard_v1.0.PcbDoc` | 主板 PCB v1.0 |
| `PowerSupply_v1.1.SchDoc` | 电源板原理图 v1.1 |
| `CommModule_v2.0.SchDoc` | 通信模块原理图 |

### 2.2 Gerber 打样包命名

```
{项目名}-gerber-v{版本}-{日期}.zip
```

示例：
```
wm-us-lora-my-jig-gerber-v1.0-20241220.zip
```

### 2.3 BOM 命名

```
bom-{板名}-v{版本}.xlsx
```

示例：
```
bom-mainboard-v1.0.xlsx
bom-tester-v1.1.xlsx
```

### 2.4 硬件版本目录

```
hardware/tester/
├── sch/
│   ├── v1.0/
│   ├── v1.1/
│   └── v2.0/
└── pcb/
    ├── v1.0/
    └── v2.0/
```

**版本号规则：**
- `v1.0` → `v1.1`：小改，修 bug、优化布线
- `v1.x` → `v2.0`：大改，结构变化、功能增减

---

## 三、固件文件命名规则

### 3.1 固件二进制命名

```
{项目名}-firmware-v{版本}.{扩展名}
```

示例：
```
wm-us-lora-my-jig-firmware-v1.0.0.bin
wm-us-lora-my-jig-bootloader-v1.0.0.hex
```

### 3.2 带 MCU 型号（可选）

```
{项目名}-{MCU型号}-firmware-v{版本}.bin
```

示例：
```
wm-us-lora-my-jig-fm33lg04x-firmware-v1.0.0.bin
```

---

## 四、软件/代码命名规则

### 4.1 Python 文件命名

- 全小写
- 单词用下划线 `_` 连接
- 避免缩写，保持可读

| 文件 | 说明 |
|------|------|
| `main.py` | 程序入口 |
| `test_flow.py` | 测试流程 |
| `protocol_parser.py` | 协议解析 |
| `serial_driver.py` | 串口驱动 |
| `mes_client.py` | MES 客户端 |
| `config_loader.py` | 配置加载 |

### 4.2 配置文件命名

```
config/
├── default.yaml                # 默认配置
├── config.debug.yaml           # Debug 覆盖
└── products/
    ├── {地区}-{通信方式}.yaml   # 产品特定配置
    ├── my-lorawan.yaml
    ├── cn-nbiot.yaml
    └── eu-mbus.yaml
```

### 4.3 类命名（Python）

- PascalCase（大驼峰）
- 清晰表达职责

```python
class TestFlowController:
class ProtocolParser:
class SerialPortDriver:
class MesClient:
```

### 4.4 变量和函数命名

- snake_case（小写下划线）
- 动词开头（函数）

```python
# 变量
test_result = {}
serial_port = "/dev/ttyUSB0"
retry_count = 3

# 函数
def run_test_flow():
def parse_response(data):
def connect_to_mes():
```

---

## 五、文档命名规则

### 5.1 Markdown 文档

- 全小写
- 单词用 `-` 连接
- `.md` 扩展名

| 文件 | 说明 |
|------|------|
| `protocol-mcu.md` | MCU 通信协议 |
| `protocol-mes.md` | MES 通信协议 |
| `test-flow.md` | 测试流程 |
| `test-steps.md` | 操作步骤 |
| `troubleshooting.md` | 故障排查 |

### 5.2 规格文档

```
{类型}-{描述}-{版本}.{格式}
```

示例：
```
spec-hardware-v1.0.pdf
spec-requirements-v1.0.md
datasheet-fm33lg04x.pdf
```

---

## 六、版本号规则

采用语义化版本 [SemVer](https://semver.org/)：

```
{主版本}.{次版本}.{修订号}
v1.2.3
```

| 部分 | 何时增加 |
|------|----------|
| 主版本 | 不兼容的重大变更（破坏性改动） |
| 次版本 | 向下兼容的新功能 |
| 修订号 | Bug 修复、小优化 |

**示例：**
```
v1.0.0  初始发布
v1.0.1  修复串口超时问题
v1.1.0  新增 MES 对接功能
v2.0.0  重构测试流程，协议不兼容
```

---

## 七、Git 相关命名

### 7.1 分支命名

| 分支 | 说明 |
|------|------|
| `main` | 稳定版本，可发布 |
| `dev` | 开发分支（可选） |
| `feature/{功能名}` | 功能开发 |
| `fix/{问题描述}` | Bug 修复 |

示例：
```
feature/mes-integration
feature/add-pressure-test
fix/serial-timeout
fix/config-loading-error
```

### 7.2 Commit 消息

```
{类型}: {简短描述}

{详细说明（可选）}
```

类型：
| 类型 | 说明 |
|------|------|
| `feat` | 新功能 |
| `fix` | Bug 修复 |
| `docs` | 文档更新 |
| `refactor` | 重构 |
| `test` | 测试相关 |
| `chore` | 杂项（配置、依赖等） |

示例：
```
feat: 新增 MES 通信模块
fix: 修复串口超时未重试问题
docs: 更新测试流程说明
refactor: 重构协议解析逻辑
```

### 7.3 Tag 命名

```
v{版本号}
```

示例：
```
v1.0.0
v1.1.0
v2.0.0
```

### 7.4 Release 命名

```
{项目名} v{版本号}
```

描述中包含：
- 变更内容
- 附件清单（Gerber、固件、软件包）

---

## 八、快速参照表

### 产品类型速查

| 中文 | 编码 | 示例仓库名 |
|------|------|------------|
| 水表 | `wm` | `wm-us-lora-my-jig` |
| 气表 | `gm` | `gm-hl-cn-jig` |
| 膜表 | `dm` | `dm-pcba-jig` |
| 多元 | `dv` | `dv-valve-jig` |
| 通信模块 | `cm` | `cm-cat1-jig` |
| 压力监测 | `pm` | `pm-nb-jig` |
| 热量表 | `tm` | `tm-us-jig` |

### 计量方式速查

| 中文 | 编码 |
|------|------|
| 超声波 | `us` |
| 霍尔 | `hl` |
| 机械 | `mc` |
| 电磁 | `em` |

### 通信方式速查

| 中文 | 编码 |
|------|------|
| LoRaWAN | `lora` |
| NB-IoT | `nb` |
| Cat-1 | `cat1` |
| 4G | `4g` |
| WiFi | `wifi` |
| M-Bus | `mbus` |
| 有线 | `wired` |

### 地区速查

| 中文 | 编码 |
|------|------|
| 国内 | `cn` |
| 马来 | `my` |
| 欧洲 | `eu` |
| 东南亚 | `sea` |
| 国际 | `intl` |

### 尺寸速查（可选后缀）

如果需要区分口径，可在项目名末尾添加：

| 口径 | 后缀 |
|------|------|
| DN15 | `-dn15` |
| DN20 | `-dn20` |
| DN25 | `-dn25` |
| DN32 | `-dn32` |
| DN40 | `-dn40` |
| DN50 | `-dn50` |

示例：`wm-us-lora-my-dn20-jig`

### 年份标记（可选）

通常不需要年份，但如果同一产品有明显的年度迭代：

```
wm-us-lora-my-2024-jig
wm-us-lora-my-2025-jig
```

或者用版本号区分更合适。

---

## 九、命名决策流程图

```
开始
  │
  ├─ 是否是多元项目？
  │   ├─ 是 → dv-{自定义描述}-jig
  │   └─ 否 ↓
  │
  ├─ 确定产品类型 → wm/gm/dm/cm/pm/tm
  │
  ├─ 是否需要区分计量方式？
  │   ├─ 是 → 添加 us/hl/mc/em
  │   └─ 否 → 跳过
  │
  ├─ 是否涉及通信？
  │   ├─ 是 → 添加 lora/nb/cat1/...
  │   └─ 否 → 跳过
  │
  ├─ 是否区分地区？
  │   ├─ 是 → 添加 cn/my/eu/...
  │   └─ 否 → 跳过
  │
  ├─ 是否区分工装类型？
  │   ├─ 是 → 添加 func/comm/pcba/...
  │   └─ 否 → 跳过
  │
  └─ 拼接 + 末尾加 -jig → 完成
```

---

## 十、FAQ

**Q: 字段顺序可以调整吗？**
A: 建议保持 `产品-计量-通信-地区-工装类型-jig` 的顺序，便于排序和查找。

**Q: 某个字段不适用怎么办？**
A: 直接省略。比如纯通信模块测试，没有"计量方式"，就写 `cm-cat1-jig`。

**Q: 名字太长怎么办？**
A: 只保留必要字段。`wm-lora-my-jig` 比 `wm-us-lora-my-prod-jig` 更简洁，够用就行。

**Q: 多元项目实在没规律？**
A: 用 `dv-{你觉得合适的简短描述}-jig`，保持可读即可。

**Q: 需要同时支持多种通信方式？**
A: 如果是同一个工装支持多通信，用最主要的命名，或用 `multi`：`wm-us-multi-jig`。

---

## 附录：完整命名示例库

| 场景 | 仓库名 |
|------|--------|
| 马来超声波水表 LoRaWAN 产线测试 | `wm-us-lora-my-jig` |
| 国内超声波水表 NB-IoT 产线测试 | `wm-us-nb-cn-jig` |
| 国内霍尔水表产线测试 | `wm-hl-cn-jig` |
| 霍尔气表通用测试 | `gm-hl-jig` |
| 膜式燃气表 PCBA 测试 | `dm-pcba-jig` |
| Cat-1 通信模块测试 | `cm-cat1-jig` |
| LoRaWAN 通信模块测试 | `cm-lora-jig` |
| NB-IoT 压力监测终端测试 | `pm-nb-jig` |
| 超声波热量表测试 | `tm-us-jig` |
| 多元-阀门控制器测试 | `dv-valve-ctrl-jig` |
| 多元-显示屏单元测试 | `dv-display-jig` |
| 欧洲 M-Bus 水表测试 | `wm-mbus-eu-jig` |
| DN20 专用超声波水表测试 | `wm-us-dn20-jig` |
