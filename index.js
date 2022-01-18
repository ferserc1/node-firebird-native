const testAddon = require('./build/Release/node-firebird.node');

const host = process.argv[2] || "localhost";
const dbFile = process.argv[3] || "/home/fernando/desarrollo/TEST.FDB";
const user = process.argv[4] || "SYSDBA";
const pass = process.argv[5] || "masterkey";
const query = "SELECT * FROM PERSON";
if (process.argv.length>2 && process.argv.length<6) {
    console.error("Invalid parameters");
    console.log("Usage with no parameters: default connection to:");
    console.log(`   host: ${ host }`);
    console.log(`   dbFile: ${ dbFile }`);
    console.log(`   user: ${ user }`);
    console.log(`   pass: ${ pass }`);
    console.log("Usage with parameters: you must to specify host, dbFile, user and password");
    console.log("node . localhost /home/myuser/TEST.FDB SYSDBA masterkey");
    return;
}

console.log("Connection to database:");
console.log(
`   host: ${ host }
    dbFile: ${ dbFile }
    user: ${ user }
    pass: ${ pass }`);

console.log("\n\nResult:\n");

console.log(testAddon.runSimpleTest(
    host,
    dbFile,
    user,
    pass,
    query
));

module.exports = testAddon;