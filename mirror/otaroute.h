server.on("/", HTTP_GET, []() {
server.sendHeader("Connection", "close");
server.send(200, "text/html", loginIndex);
});
server.on("/serverIndex", HTTP_GET, []() {
server.sendHeader("Connection", "close");
server.send(200, "text/html", serverIndex);
});
server.on("/collect", HTTP_POST, []() {
int paramsNr = server.args();
String message = "Recieved. Param number: ";
message += paramsNr;
if (paramsNr >= 1) {
message += " First arg name: ";
message += server.argName(0);
if (server.argName(0) == "info") {
Serial.print("Recieved data: ");
Serial.println(server.arg(0));
updateHA(server.arg(0));
message += " Recieved data: ";
message += server.arg(0);
}
}
server.sendHeader("Connection", "close");
server.send(200, "text/plain", message);
});
server.on("/update", HTTP_POST, []() {
server.sendHeader("Connection", "close");
server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
ESP.restart();
}, []() {
HTTPUpload& upload = server.upload();
if (upload.status == UPLOAD_FILE_START) {
Serial.printf("Update: %s\n", upload.filename.c_str());
if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
Update.printError(Serial);
}
} else if (upload.status == UPLOAD_FILE_WRITE) {
if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
Update.printError(Serial);
}
} else if (upload.status == UPLOAD_FILE_END) {
if (Update.end(true)) {
Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
} else {
Update.printError(Serial);
}
}
});
server.begin();
