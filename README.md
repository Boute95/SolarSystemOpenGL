# SolarSystemOpenGL

## Architecture
### Global Architecture
The engine is the heart of the application. It owns the program main loop and the different main blocks of it :
- The RenderEngine, managing the render
- The PhysicsEngine, managing the simulation of the planets (i.e there orbit) and the time of the simulation
- The ControlsManager, managing user inputs
- The CameraController, owning and managing the camera
- The SolarSphere objects, i.e the planets, moons,...
- The SkyBox, drawing a galaxy in the background 

![Global Architecture](http://www.plantuml.com/plantuml/png/SoWkIImgAStDuNBDIy_CIrNGrTLIK39KKWXApKj9BO88eii5P5GMPoONOvTqpiyhAShFAVPDp4jCJot2a4xCJIrAX2hAGPFNKb88piz9B0eko4WjmZ0vEBlIAR-22mYISnABYnMWqjMr43xKoMYYCCUY2MEu0ow3vW641BBJu89GHu7u3a3hWG490000)

### The Control Manager
The ControlManager makes actions at each main loop iteration according to user input. It tells the PhysicsEngine to change the time or the CameraController to change camera orientation or zoom.

![ControlsManager](http://www.plantuml.com/plantuml/png/RP5D2i8m48NtESNGPMaBRbr8iRWKn9vWY4CRp8yayQUATpTYA3NjSjutyoPvKpkFrb-LP3lT2KrGbZbagmoEf4zaVsBA3ltW17VBi37QMoFT7ZLsP6SO5LcCJJBXUGQjaMZRIqzsvjoUXwrvi6H1m9kPAwoXwL5tvE0cw5x0qnXLL5MrEFttdyce5ue0EQVWY5uOpHZZ4fs3sFfwnpgcbQZHDvNJnuuapMu4qrH6CURnhUkmFjpm0m00)

### Interfaces used by the RenderEngine and PhysicsEngine
-The RenderEngine stores a list of `Drawable` and render at each iteration by calling their draw() method. This takes the projection matrix and the view matrix from the `RenderEngine`.
-On the other hand, the `PhysicsEngine` stores a list of `Simulable`. It has methods to set its orbit informations. A `Simulable` is also a `Transformable`, having methods to translate, rotate, scale and getting its transform matrix. At each iteration, the `PhysicsEngine` calls the `Simulable`'s `update()` method taking the current time as parameter, moving correctly the object in function of its orbit.

![Interfaces](http://www.plantuml.com/plantuml/png/VLHDRzD04BtxLwnoSafQ2S6vAXyLL6f4L2CkYCDqFR67hdVDx3XD5FBViHrZDXlJd3pllNdZUT7unWkmD9L9Rcr15jNbvOMQlPwf1xGvyX6CkLMvywJzDFd1MM5d_18i5CXdD5J8C8XCn5_CLEOCS5QNo6VEsTFklTicqO2MlZvpdH95htrIgQkhOJnLZO57WyaOG4X_P7Z-FtjFHIcPQrXZCXgretzVgwyCrgyTLtrtGbQGrw1nT5JxHBM_Lnj7kSfRCAr0tggQtSyb2DDseNfWG_Xy1ER7Xgo46hyX2sw__r05IlTC6dqw3nmzogVx8OnqV5A5MKQgrYvl9PamsK9j_0gaNAYXNFVbF3a46mIhnMj8nnWGJ3UetuI3s4a7vwxfUXZoXUea2hRa9tI_6X1aIyw6fDTW9gpHeuplDARGXrS4p374D5hctz-sFyrb1OnMqjDbNHJUkzf1xScd_J9FLKIlaEab_Wi_ae2vrHgjC6cItT-8S5hQEReyNHi7eahNi8zq3rs0vEovSDhmpcf3jcyPn3aMZ7WYR-eS10TUgC8x-xcrxAFK1hnNms7i3qCzdak8ZWSPmV4n1qnqrICHV3L6SFXUTFLDExwfp1y0)

### The SolarSphere using the Decorator pattern
As we said, the `Engine` owns all the `SolarObject`s. The `RenderEngine` uses `Drawable`s and the `PhysicsEngine` uses `Simulable`s. Thus, the `SolarObject` naturally implements the `Drawable` and `Simulable` interfaces.
A solar object can have different additional characteristics : it can be a light source if it's a star, it can have rings if it is a planet, with moons, an orbit line, etc. This is why we use here the Decorator pattern to customize and add properties to a SolarObject.

![SolarSphere](http://www.plantuml.com/plantuml/png/VLHDSzCm4BtxLsXwSalQ2voP0kr0XcR891qk38UDl754PScirccOqF-ER2l-K4tYY_tUqzFkoqgtZe6uAdIojXfeNUwGKDpS_7qlxWYUOQFnDRDMHQLZwYEuGFVWI727qXAmfTUgUvChW-Bw-afSN5sCg6-qKVpGic5Lx9UibCdFq5svhUQHmBYjfIBkmDDssY5XcoDxJ1mJPHXf2nAxW3me_E_DtgfCP1vC2-1teYJxQm5CwZ0J3R1N-Dm2b-s2zGvA_8x4UFZnK-J8zRkIwDBBWQD3_lom00CvKjgzYLml8fMtoxnapLJdiNTBuDrCXCzjytcPl2I33leeuZQuPZGmfdkKRuSRaUKQpcnLho78PgAM23WeDw7xNG4Z6MNDg5e9Ui8Q7N9NKvT24ru-ODeGqwYP_cy-ZdDP0g7XTDoiZSBxK5eedN9DKUAfYEWbaZh7DsCA-bvAD4nAAlvpYWYdfRMZpTAjji1YPojoaMvL1wYiEI_i3UT6QcMQ9K6SOKw88tbLPi0OU5O5piqNR-cZz8_Ku9m8X_7uCZtr_G4P1mrPzibgIuzuu8hmD8PbFNMTTtnV18C87WoNgjpSV2qYX-XyHZOZBXtMk_7clLLpROIbzVjfMsKCqghPUoO2PYlkiVzRzhTLyEs0TcvadT1CXFXtIZuPTDEE_hb5arM5_WS0)

### The GLManager
All code directly related to OpenGL is regrouped into the `GLManager`. Its methods are used in the `render()` method of the `RenderEngine` and in the `draw()` method of the `Drawable`.

![GLManager](http://www.plantuml.com/plantuml/png/bLJDZjem4BxdAUPK6JMSMlMmxQM22bK2jIhRvO0u3F6Gp3QnaJC9h5Rxxar2_YEXbWEov_lnZEmlg_K63ORauCjy3h_8Q7BVJCY6l26qT7Z1OqoU5yIOfj2XhnuKl_UvPGsezHCvuO1IjOtmJEMEhli3vBCUJHTcBM-r9fCba5XDVc7BHY2lL0kR6PaDtGjJJKvjnR49uG-z-52ly_GdIjHkJzLszhadprAQo4VslmsVh4iQ0kiQFreRGuJf1E_hKv8QVy8ueuvKZzKrSvzyYYt-CpcCauU7d88Fx_vBaQ1yd2YA9cd7MY9LjG2NXh1QP-MreDQFT9NCaVgUO4Z0IJYbBB8ZRV0yOEu_7O3BHJe-ysiWd5DDRjgCRO32rlXGsvPzr-z4RjHYEl6RpUFBcGR6PCgtMiwZ1dNDQGTC1KiwIxHpB5FPFVZ8HWyhcPdMWfZGbQKtpsCZv4uOK9ihU1tbGvLN16TddpSeZgy-L8MSwN8hr4zl6BEGf0tMw6ssYLNj2i9uCsAr2RaJAk-j-GhqFnZr1FDs8djyfa3I_U5sGf-hjilrZessbwQJ2vjwwSC24t88mIYSFoe_rVcFy3M7aQZgVsip5n34VOQhpbUpwPMKy_m5)
### SkyBox
![Skybox](http://www.plantuml.com/plantuml/png/NP11IyD048Nlyok6dX9j2u9ub2AA5mD2n4lfOSnEjwlf9inEqvNQ_-xQ3QMufvd7UnyxRn6KH7VR5kglxuSkudp-Su-FGdlwQ1cUl7MUSJQxmidD1BC7m7bbMLF3PoSU0DEx7Zfdq2Ins9BUOY_TPqKgBaxn90oEzraeSw3UKC_lBCfnkKBB-ZUxXaDHNX03w_DBHPuiIt6UqBRLFrV2cMIfLPotE8HNqiqKntLzMaiu0ZGjXJ3Ua_-U4MJC6qVT2OSHihnROPzYuIANQpaSOS7UfF9-0G00)

### Cameras and View
![Camera](http://www.plantuml.com/plantuml/png/TP9FRnCn4CNl_XIZd9AIhSIV4qAegD0JI5LR43rExCbYyDfXFBkj2dntibvli-usj_ZzNjuyp_ei2hAqZLFds10Zd9x-VGytZ3vk0pUuSPJ9UV32mJbYgAeJM9miu9kbkoFqvG86eAx86-9FlhQUu5rLPHtUmlMUHBZay3CbmHSKjfgYokOow311AUk5U8kQogRmHm40lEY2DI0zSIYqx4Y_Naq81-bb4zh-Func3Rq5yDx6Pto_MnHYRuEVmgZHFHDDaUInKrncrg2yWNf2qbNlz_YVKjfXZ6a3HVyXIF_Qe7Df3WXoJRA6NDpOAEWrNN1eRag4ldRqlJpUhihm2oOgSzDX5wALmrqt8JYmyT0awybRamo3dwgNEMJKSuyz-JWhFVTyIEsFwBVJfStUNbxWKttyrXXtfEKAnOQS7adwpI-lXQslmPhry2MwaTzPqJzAouZIEHNJOZjAfldx-KnR6USRgfbexlcwE-vu2A4PwSDgUhz-zF1hlfFPKnfstP5-1PBSP-HDsxZ_)
### Full program architecture
![Full program architecture](http://www.plantuml.com/plantuml/png/fLHDJzmm4BtdLrWS4R7KQrKXn5BriWX4gjvdtI5h6jjex2sb7_-z9ZPsDivcqyA5UERD6y_pcxsm3iZjL5UjG271ocX7fkkGU0Wmpd-Viyy4sjuRKh3fi8IE0wokJzd9wGaha5yaFYsjVrVMHsJ943_jDMXeUu9pThpDUxRQWcxHik_-NcVifp7gZ7E-ZFzs-sobi3p-_wXRgN70wQH21aAW9m0dZQu29AdJc0weUTmYuStc0OMpV12AwAH5y-tvqlmOH-zGVqMIkkNXAwH7gEAgaw3HZ4Nwc9pLn3mtj95k7MYyZ-Odla9X29oXQbfQpeDkhzb6gbtNEt9QXLIGqrS4J_zMiPRjrZLcH-9WqOUwFgIEjqFZePRTadbWB-vdr-182hHJSjrvxlzJAcdXouk5BUSFQnqiTJWzxy_vTA0ehdUiggxDujddSPTWtp97qMuHLvRoqphkKM-FIUVCmGl3-Z-f7T8z2Dn_NbPLeWDhnmkSug6PFsfGQ1yzmUkxi5yHihTeWqRPLjMVN9xlbmY6OyLG6cd0byR9eRnWVPDO7AsPUnORbbg7H3WKg13kDszlWl8T4z_8GsKqEp1DCKp7WlJJ5yylk-slSE65sgdkBm00)
