#!/usr/bin/env python
# coding: utf-8

# In[13]:


import numpy as np
import math as math
import matplotlib.pyplot as plt


# In[14]:


def eq1(x):
    r1 = 100000
    r2 = 666
    c1 = 1e-6
    c2 = 1e-9
    ans = 1/(np.sqrt(  ((1-((x**2)*r1*r2*c1*c2))**2) + ((x*(r1+r2)*c2)**2) ))
    return ans


# In[15]:


def eq2(x):
    r1 = 100000
    r2 = 666
    c1 = 1e-6
    c2 = 1e-9
    ans = -np.arctan((x*(r1+r2)*c2) / (1-(x**2)*r1*c1*r2*c2))
    return (ans*180)/math.pi


# In[18]:


w = [i/(2*math.pi) for i in range (1,100000)]
a = [eq1(i) for i in w]
ang = [eq2(i) for i in w]
fig = plt.figure()
Hw = fig.add_subplot(2,1,1)
plt.xlabel(r'Frequency, $\omega$/2$\pi$ (Hz)')
plt.ylabel(r'|H($\omega$)')
line, = Hw.plot(a, color ='black', lw=2)

Hw.set_xscale('log')
Hw.set_title('Magnitude and phase response')
angle = fig.add_subplot(2,1,2)
line, = angle.plot(ang, color='blue', lw=2)
angle.set_ylabel("angle")
angle.set_xlabel("frequency")
angle.set_xscale('log')
plt.show()


# In[19]:


#swap r1 c1, r2 c2

def eq1(x):
    r1 = 1e-9
    r2 = 1e-6
    c1 = 100000
    c2 = 666
    ans = 1/(np.sqrt(  ((1-((x**2)*r1*r2*c1*c2))**2) + ((x*(r1+r2)*c2)**2) ))
    return ans


# In[33]:


def eq2(x):
    r1 = 2e-9
    r2 = 1e-6
    c1 = 100000
    c2 = 666
    ans = -np.arctan((x*(r1+r2)*c2) / (1-(x**2)*r1*c1*r2*c2))
    return (ans*180)/math.pi


# In[35]:


w = [i/(2*math.pi) for i in range (1,100000)]
a = [eq1(i) for i in w]
ang = [eq2(i) for i in w]
fig = plt.figure()
Hw = fig.add_subplot(2,1,1)
plt.xlabel(r'Frequency, $\omega$/2$\pi$ (Hz)')
plt.ylabel(r'|H($\omega$)')
line, = Hw.plot(a, color ='black', lw=2)

Hw.set_xscale('log')
Hw.set_title('Magnitude and phase response')
angle = fig.add_subplot(2,1,2)
line, = angle.plot(ang, color='red', lw=2)
angle.set_ylabel("angle")
angle.set_xlabel("frequency")
angle.set_xscale('log')
plt.show()


# In[ ]: