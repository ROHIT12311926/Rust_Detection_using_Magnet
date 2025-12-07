📌 1. Project Overview

This project detects rusted vs non-rusted regions on a ferromagnetic cylindrical rod using the MLX90393 3-axis magnetometer.
When the sensor moves over the metal surface, the magnetic field value changes due to:

Rust altering magnetic permeability

Flux leakage

Distorted magnetic domains

These distortions appear in the X, Y, Z magnetic components, which are collected, processed, visualized, and fed into a machine learning model to classify rust.

📌 2. Hardware Used

MLX90393 – 3-Axis Magnetometer

ESP32 DevKit (I²C Communication)

Test Rod (MS / CRC Pipe)

Linear Motion Setup / Manual Sliding

Power Supply (3.3V)

📌 3. Working Principle (How the Sensor Detects Rust)
🔹 Hall Effect

MLX90393 works on Hall Effect.
Whenever magnetic field 
𝐵
B changes, Hall voltage 
𝑉
𝐻
V
H
	​

 changes:

𝑉
𝐻
=
𝐼
𝐵
𝑛
𝑞
𝑡
V
H
	​

=
nqt
IB
	​

🔹 Rust Distorts Magnetic Flux

Rusted metal has:

Lower magnetic permeability (μ)

Broken magnetic domains

Non-uniform surface

As a result:

The magnetic field B becomes unstable

MLX90393 outputs fluctuating X, Y, Z values

These abnormalities indicate rust presence

📌 4. Project Flow (START → END)

Ye tumhare project ka step-by-step flow hai —
exactly interview / GitHub dono me chalega.

STEP 1 – Data Collection

Sensor ko rod ke upar slide karke readings li.

For each Length value (10.5 cm, 11 cm, …):

X axis magnetic field

Y axis magnetic field

Z axis magnetic field

Resultant field

𝑅
=
𝑋
2
+
𝑌
2
+
𝑍
2
R=
X
2
+Y
2
+Z
2
	​


Label: RUSTED / NON-RUSTED

Material: MS / CRC

Data CSV / Excel me store kiya.

STEP 2 – Data Cleaning

Null values remove

Outliers inspection

Wrong readings fix

Column renaming

Convert strings → numeric

STEP 3 – Split Rusted vs Non-Rusted
df_non_r = df[df['Output'] == 'NON-RUSTED']
df_r = df[df['Output'] == 'RUSTED']


CRC and MS material datsets also separated.

STEP 4 – Data Visualization (Most Important Part)

Generate 4 main graphs:

Resultant vs Length

X vs Length

Y vs Length

Z vs Length

Each graph compares:

Blue = Non-Rusted

Red = Rusted

Ye graphs clearly dikhate hain:

Rusted metal → more fluctuations, spikes, dips

Non-rusted → smooth curve

Z-axis most sensitive

STEP 5 – Understanding Magnetic Behaviour

Key observation:

Parameter	Non-Rusted	Rusted
Resultant	Smooth	Distorted
X	Slight variation	Sharp fall / rise
Y	Mild curve	Big spikes (rust effect)
Z	Stable	Deep drop (rust region)

Reason:

Rust changes magnetic permeability μ

Flux leakage hota hai

Magnetometer Hall voltage distort hota hai

STEP 6 – Machine Learning Pipeline

Machine learning classifier trained to detect rust based on:

X, Y, Z values

Resultant

Material (MS / CRC)

Length

Model Training Steps

Train-test split

Normalization

RandomForest / SVM classifier

Model evaluation

Saving model (joblib)

Prediction function

STEP 7 – Model Output

Given any new magnetic reading:

If magnetic signature smooth → NON-RUSTED

If signature distorted/noisy → RUSTED

STEP 8 – Final Deployment

ESP32 reads sensor values → sends to Python ML model → model predicts → display result.

Future scope: Drones / robots scanning pipelines & detecting rust automatically.

📌 5. Why Magnetic Method Works

Because magnetic field = function of metal’s domain structure.

Rust:

Reduces permeability

Breaks alignment

Weakens magnetic response

This distortion is picked up by MLX90393.

📌 6. Applications

Oil & gas pipelines

Railway tracks

Aircraft bodies

Industrial machine inspection

Structural health monitoring

📌 7. Conclusion

“MLX90393 accurately captures magnetic field disturbances caused by rust.
Combining these readings with ML visualization and classification creates a powerful, contactless rust detection system.”
