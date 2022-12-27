#this app open a gif and use it for showing on oled or other mono chromicdisplays
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import serial

            #fname ,repeat, level
F_NAMES=[  
         ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\26.gif",1,100],
         ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\0.gif",1,100],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\1.gif",5,100],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\2.gif",1,100],
            ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\3.gif",1,210],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\4.gif",1,60],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\5.gif",1,60],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\8.gif",1,100],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\9.gif",1,100],
            ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\10.gif",1,60],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\11.gif",1,100],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\12.gif",1,100],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\13.gif",5,60],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\17.gif",5,80],
        #    ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\18.gif",1,100],
            ["C:\\Users\\tOpak\\Documents\\python\\gif_oled\\24.gif",20,220]

         ]
LCD_SIZE=[128,64]
########################################################################################
#   gifToImageList
def gif2list(fname,test=False):
    try:
        im=Image.open(fname)
    except IOError:
        return []
    
    frmaes=[]
    cnt=0
    base_name=fname.replace(".gif","")
    try:
        while 1:
            im_frame=Image.new("RGB",im.size)
            im_frame.paste(im)
            frmaes.append(im_frame)
            cnt+=1
            if test:
                im_frame.save(base_name+"_"+str(cnt)+".png")
            im.seek(im.tell()+1)
    except EOFError:
        return frmaes
    return frmaes

##########################################################################################
#convert size to prefered size for oled screens
def frame_size_converter(frame,size:tuple):
    return frame.resize(size)


#########################################################################################
def rgb2gray(rgb):
    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b
    return gray

def frames_to_gray_array(frame):
    im_ar=np.asarray(frame)
    return rgb2gray(im_ar)
        
###########################################################################################
def gray_frame_to_lcd_raw(frame,level=40):
    frame[frame<level]=0
    frame[frame>0]=1
    frame_size=frame.shape
    L=frame_size[1]
    H=(frame_size[0]+7)//8
    frame_lcd=np.zeros([H,L])
    for h in range(H):
        for l in range(L):
            frame_lcd[h,l]=frame[8*h,l]+2*frame[8*h+1,l]+4*frame[8*h+2,l]+8*frame[8*h+3,l]+16*frame[8*h+4,l]+32*frame[8*h+5,l]+64*frame[8*h+6,l]+128*frame[8*h+7,l]
    return frame_lcd

###########################################################################################
def pack_frame_to_raw_byte(frame):
       frame=frame.astype(np.uint8)
       shape=frame.shape
       L=shape[1]
       H=shape[0]
       dat=frame.reshape((1,L*H))[0]
       return bytes(dat)



#lcd_port=serial.Serial("COM6",baudrate=921600*4)
lcd_gif_data=[]
try:
    for fname in F_NAMES:
        lcd_gif_data.append(gif2list(fname[0]))
    
    ix=0
    IX=len(lcd_gif_data)
    
    repeat=50
    while repeat:
        repeat-=1
        data=lcd_gif_data[ix]
        cnt=F_NAMES[ix][1]
        level=F_NAMES[ix][2]
        ix=(ix+1)%IX 
        for _ in range(cnt):
            for frame in data:
                sized_frame=frame_size_converter(frame,LCD_SIZE)
                gray_frame=frames_to_gray_array(sized_frame)
                lcd_frame=gray_frame_to_lcd_raw(gray_frame,level)
                lcd_byte=pack_frame_to_raw_byte(lcd_frame)
                plt.imshow(gray_frame, animated=True)
                plt.show(block=False)
                #lcd_port.write(lcd_byte)
                #lcd_ack_flag_for_next_token=lcd_port.read()
                plt.pause(0.0000000001)
except KeyboardInterrupt:
    print("Pouyalnx ,LnxEBM 25/12/2022 all right reserved. all steps for design EbmMachine.2023 happy new Years")


#lcd_port.close()



