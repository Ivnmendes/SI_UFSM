#!/bin/bash
set -e
./gradlew clean shadowJar
java -jar build/libs/TrabFactoryPattern-1.0-SNAPSHOT-all.jar