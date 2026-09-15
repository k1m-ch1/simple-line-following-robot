So we want our angle at which the ir sensor still detect the line to be around 45 to 60 degrees.

So if the distance from the furthest sensor to the middle is $x$, and the distance between the "axel line" and the sensor itself is $r$, then:

$$
\tan \theta = \frac{x}{r}
$$


So, if we actual heading in PID (not very accurate, but I think it's a good mapping):

$$
\theta = \arctan {\frac{x}{r}}
$$

In our case:

- $x \approx 27.5mm$

For $\theta = 60$:

$$
r = \frac{x}{\tan\theta} = \frac{27.5}{\tan 60} = 15.9mm
$$

For $\theta = 30$ meanwhile:

$$
r = 47.63mm
$$

# Microcontroller

I'll try to use the stm32 blue pill for this project because it's high in abundance in terms of I/O. The downside though is that it requires an st-link, and uploading requires like messing around with the jumpers.

I'll see whether using platform io will make this process a bit easier.

Pins:

```
PA0  ADC1_IN0
PA1  ADC1_IN1
PA2  ADC1_IN2
PA3  ADC1_IN3

PA4  ADC1_IN4
PA5  ADC1_IN5
PA6  ADC1_IN6
PA7  ADC1_IN7

PB0  ADC1_IN8
PB1  ADC1_IN9

PC0  ADC1_IN10
PC1  ADC1_IN11
PC2  ADC1_IN12
PC3  ADC1_IN13
PC4  ADC1_IN14
PC5  ADC1_IN15
```

So these all support ADC, meaning that we can have like 2 of these 8 way line sensors!

Anyway, in the platformio world, we can just use `analogRead` for ADC. It's just that it's going to be 12 bits now, which is pretty neat.

## UART

So on the board, A is going to refer to PORT A probably.


### UART 1

```
PA9  → TX
PA10 → RX
```

### UART 2

```
PA2 → TX
PA3 → RX
```

### UART 3

```
PB10 → TX
PB11 → RX
```

## SPI

### SPI 1

```
PA5 → SCK
PA6 → MISO
PA7 → MOSI
```

### SPI 2

```
PB13 → SCK
PB14 → MISO
PB15 → MOSI
```

## I2C

```
PB6 → SCL
PB7 → SDA
```

# Safe GPIO

Safe:

```
PA0–PA7
PB0–PB1
PB5–PB9
PC0–PC15
```

Don't use:

```
PA13 → SWDIO
PA14 → SWCLK
```

## Interrupts

External interrupts are defined like this:

| EXTI line  | Possible GPIO pins    |
| ---------- | --------------------- |
| **EXTI0**  | PA0, PB0, PC0, ...    |
| **EXTI1**  | PA1, PB1, PC1, ...    |
| **EXTI2**  | PA2, PB2, PC2, ...    |
| **EXTI3**  | PA3, PB3, PC3, ...    |
| **EXTI4**  | PA4, PB4, PC4, ...    |
| **EXTI5**  | PA5, PB5, PC5, ...    |
| **EXTI6**  | PA6, PB6, PC6, ...    |
| **EXTI7**  | PA7, PB7, PC7, ...    |
| **EXTI8**  | PA8, PB8, PC8, ...    |
| **EXTI9**  | PA9, PB9, PC9, ...    |
| **EXTI10** | PA10, PB10, PC10, ... |
| **EXTI11** | PA11, PB11, PC11, ... |
| **EXTI12** | PA12, PB12, PC12, ... |
| **EXTI13** | PA13, PB13, PC13, ... |
| **EXTI14** | PA14, PB14, PC14, ... |
| **EXTI15** | PA15, PB15, PC15, ... |

So basically, if PA0 uses external interrupts, then PB0, PC0,.. can't use it.

## PWM and bluepill max resolution

Seems like: `16-bit` has a max frequency of `1098.6 Hz`, so the frequency is definitely high enough Servos and even motor control (Arduino's `analogWrite` is also around 1KHz, or even less than that).

Maximum resolution is:

```
b = \log_2 (\frac{f_{timer}}{f_pwm}})
```

For DC motors, I guess a resolution of 10 bits at 20000 Hz should be fine.

## Timers

Timers are grouped as such:

| Timer    | Channels | Typical pins         |
| -------- | -------- | -------------------- |
| **TIM1** | CH1–CH4  | PA8, PA9, PA10, PA11 |
| **TIM2** | CH1–CH4  | PA0, PA1, PA2, PA3   |
| **TIM3** | CH1–CH4  | PA6, PA7, PB0, PB1   |
| **TIM4** | CH1–CH4  | PB6, PB7, PB8, PB9   |

timers should also be mapped as such:


| Pin | Possible timer channel |
| --- | ---------------------- |
| PA0 | TIM2_CH1               |
| PA1 | TIM2_CH2               |
| PA2 | TIM2_CH3               |
| PA3 | TIM2_CH4               |
| PA6 | TIM3_CH1               |
| PA7 | TIM3_CH2               |
| PB0 | TIM3_CH3               |
| PB1 | TIM3_CH4               |
| PB6 | TIM4_CH1               |
| PB7 | TIM4_CH2               |
| PB8 | TIM4_CH3               |
| PB9 | TIM4_CH4               |

So this code works:

```c
#include <Arduino.h>

#define FREQ_SERVO 50
#define DUTY_CYCLE_SERVO 0.5f

#define FREQ_MOTOR 20000
#define DUTY_CYCLE_MOTOR 0.5f

#define SERVO_PIN PA0

#define MOTOR_PIN PB7

// PB7 | TIM4_CH2               |

HardwareTimer timerServo(TIM2);
HardwareTimer timerMotor(TIM4);

void setup() {
  timerServo.setPWM(1,                     // TIM2 channel 1
                    SERVO_PIN,             // pin
                    FREQ_SERVO,            // frequency
                    DUTY_CYCLE_SERVO * 100 // duty %
  );
  timerServo.resume();

  timerMotor.setPWM(2, MOTOR_PIN, FREQ_MOTOR, DUTY_CYCLE_MOTOR * 100);

  timerMotor.resume();
}

void loop() {}
```

# Servo control

We're not using servos, but it would be nice to know how you would control it very precisely.

First of all, we have angle $\alpha$, then we have the frequency $f$. We want the "ON" pulse to be in the range between $t_{min}$ to $t_{max}$ for the full range.

So essentially, our time period $T$ is going to be $T = \frac{1}{f}$. Then our duty cyle $d = \frac{t}{T}$. Finally, if our angle is 0 to 180, we map it as such:

$$
d = \frac{t_{min} + alpha * \frac{t_{max} - t_{min}}{180}}
$$

Or a another interpretation is a linear blend:

$$
d = f * ((1 - \frac{alpha}{180})t_{min} + \frac{\alpha}{180}t_{max})
$$

We choose $t_{min} = 0.5 ms$ and $t_{max} = 2.5 ms$ for the full range.

So basically, we're blending between $0.5 \times 10^{-3} \times 50 = 0.025$ and $1.5 \times 10^{-3} \times 50 = 0.125$ in terms of duty cycle.
