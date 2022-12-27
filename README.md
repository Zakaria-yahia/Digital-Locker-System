# Digital Locker System

- Digitally secured lock based on password verification for user and master password for administrators.
- Using: Atmega32, LCD, Keypad, EEPROM and Timers.

1. Pressing on any button will make the buzzer on for 100msec.
2. First time password saved is 0000.
3. User should enter 0000 to open locker at first time.
4. To change password user should press on ‘/’  buzzer will be on for 3 second
then off  user should enter 4 digit password then  press on ‘/’ again to save
password
5. To close the locker, you should press only on ‘*’
6. To open the locker, enter 4 digit password (lcd display * each time you enter a
digit for password, then display locker opened if right password and Try again if
wrong password and a buzzer will be on for 3 second then off  re-enter
password again.
7. To reset password: (locker must be in opened state): insert 10 zeros the
password will back to default value which is 0000.


## Screenshots


![locker system project](https://user-images.githubusercontent.com/115344537/209719186-c3ae741b-fb02-4526-9c9a-68d9e6e45003.png)
