# node-firebird-native

Native connection to Firebird database using ibpp library in NodeJS

## Dependencies

On Linux, you need to install `firebird-dev` package:

```sh
sudo apt update
sudo apt install firebird-dev
```

To install a Firebird server:


```sh
sudo apt update
sudo apt install firebird3.0-utils firebird3.0-server
```

You'll be prompted to set the SYSDBA password. Here we assume that we use the default password 'masterkey'.

Then, add your user to the `firebird` group:

```sh
sudo usermod -a -G firebird your_user_name
```

## Prepare the example data

Copy the `test-data/TEST.FDB` outside the repository, to prevent modifications on the default test data file:

```sh
cp [this-repo]/test-data/TEST.FDB ~/TEST.FDB
```

You can test the connection with the interactive sql tool:

```sh
isql-fb -user SYSDBA -pass masterkey
Use CONNECT or CREATE DATABASE to specify a database
SQL> CONNECT 'localhost:/home/your_user_name/TEST.FDB';
SQL> SELECT * FROM PERSON;
ID NAME               LASTNAME
== ================== ============================
 3 Elena              Nito Del Bosque
 4 Dolores            Fuertes de Barriga
 5 Alberto            Cadiscos
```

## Build the c++ code

Install the dependencies:

```sh
npm ci
```

Use the `build` package.json script to generate the NodeJS native module

```sh
npm run build
```

## Execute the test

Use node to execute the `index.js` file with the following parameters:

```sh
node index.js [host] [dbFile] [user] [pass]
```

For example:

```js
node index.js localhost /home/youruser/TEST.FDB SYSDBA masterkey
```
