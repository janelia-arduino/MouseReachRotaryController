# RotaryPelletControllerSimple

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[StepDirControllerSimple](https://github.com/janelia-arduino/StepDirControllerSimple)

## Clients

## Devices

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["RotaryPelletControllerSimple"],
    "functions":[
      "getPelletIndex"
    ],
    "parameters":[],
    "properties":[
      "pelletsPerRevolution",
      "travelDuration",
      "reverseDirection",
      "toneFrequency",
      "toneDuration",
      "playToneBeforeMove"
    ],
    "callbacks":[
      "moveToNextPellet",
      "playTone"
    ]
  }
}
```

## API Verbose

```json

{
  "id":"getApiVerbose",
  "result":{
    "firmware":["RotaryPelletControllerSimple"],
    "functions":[
      {
        "name":"getPelletIndex",
        "parameters":[],
        "result_info":{
          "type":"long"
        }
      }
    ],
    "parameters":[],
    "properties":[
      {
        "name":"pelletsPerRevolution",
        "type":"long",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"travelDuration",
        "type":"long",
        "units":"ms",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"reverseDirection",
        "type":"bool",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneFrequency",
        "type":"long",
        "units":"Hz",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"toneDuration",
        "type":"long",
        "units":"ms",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      },
      {
        "name":"playToneBeforeMove",
        "type":"bool",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      }
    ],
    "callbacks":[
      {
        "name":"moveToNextPellet",
        "properties":[
          "travelDuration",
          "reverseDirection",
          "playToneBeforeMove"
        ],
        "functions":[
          "trigger",
          "attachTo",
          "detachFrom",
          "detachFromAll"
        ],
        "parameters":[
          "interrupt",
          "mode"
        ]
      },
      {
        "name":"playTone",
        "properties":[
          "toneFrequency",
          "toneDuration"
        ],
        "functions":[
          "trigger",
          "attachTo",
          "detachFrom",
          "detachFromAll"
        ],
        "parameters":[
          "interrupt",
          "mode"
        ]
      }
    ]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
