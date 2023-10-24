# 关于Final

## `Armor`的建立

`Armor`包含

-  装甲板的高度`obj_Height`

- 装甲板与摄像头之间的距离`Distance`
- 装甲板大小`Size`
- 装甲板颜色`Color`
- 装甲板编号`Number`

等信息，以及

- 距离测量函数`distDetect`
- 大小识别函数`sizeDetect`
- 颜色识别函数`colorDetect`
- 编号识别函数`numberDetect`

来识别装甲板上的相应信息，最后由`armorInit`函数同一初始化，由`showInfo`函数在目标处显示装甲板信息。

## 一些补充函数

1. `paramInit`

   定义在`Project.cpp`中，目的是使得`Project`能够读取存放在`WMJ/Final/src/info.txt`中的数据，从而初始化例如焦距`focal_len`的外部依赖量，是`Project`能够在不同情况下完成工作。

2. `getPixelSum`和`imgMatch`

   `getPixelSum`获得输入图片中像素的总量，该函数与`imgMatch`搭配使用可将装甲板编号部分的像素点之和与存放在`WMJ/Final/src_pic`中的样本图片逐一比较，从而确定装甲编号。

## 使用方法

假设待读取的视频的路径是`Video_PATH`，打开终端并输入

```shell
git clone https://github.com/SeeWhysimon/WMJ.git
cd ./WMJ/Final/build
cmake .
make
./Project Video_PATH ../src/info.txt
```

即可。

如果需要修改外部依赖项的参数，可以找到放在`WMJ/Final/src`中的`info.txt`文件并修改相对应的参数，或者创建位于`Info_PATH`的参数文件并按照格式

```yaml
focal_len = #value
sensor_height = #value
real_height = #value
img_height = #value
tan_judge = #value
```

输入。其中`#value`为参数所对应的值。在此基础上，打开终端并输入

```shell
git clone https://github.com/SeeWhysimon/WMJ.git
cd ./WMJ/Final/build
cmake .
make
./Project Video_PATH Info_PATH
```

即可。
