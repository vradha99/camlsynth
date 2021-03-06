open Revery;
open Revery.UI;
open Revery.UI.Components;
open AppState;
open Settings;
let component = React.component("MasterFx");

let createElement =
    (
      ~appState,
      ~parentDispatch,
      ~children as _: list(React.syntheticElement),
      (),
    ) =>
  component(hooks => {
    let fxContainer =
      Style.[
        flexGrow(1),
        alignSelf(`Stretch),
        flexDirection(`Column),
        alignItems(`Center),
        paddingHorizontal(10),
        paddingVertical(5),
        backgroundColor(Color.hex("#888888")),
        marginHorizontal(20),
        marginBottom(20),
        marginTop(-10),
        borderRadius(5.),
        height(120),
        justifyContent(`FlexStart),
        border(~width=1, ~color=Color.hex("#888888")),
      ];
    let checkboxStyle =
      Style.[
        border(~width=2, ~color=Color.hex("#EAE7C6")),
        height(15),
        width(15),
        marginRight(4),
      ];

    let fxHeaderStyle =
      Style.[
        color(Colors.black),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(12),
      ];

    let fxLabelStyle =
      Style.[
        color(Colors.black),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(12),
      ];

    let panelsStyle =
      Style.[
        flexGrow(1),
        marginHorizontal(4),
        alignSelf(`Stretch),
        flexDirection(`Row),
        justifyContent(`SpaceBetween),
      ];

    let panelStyle =
      Style.[
        flexGrow(1),
        alignSelf(`Stretch),
        flexDirection(`Column),
        justifyContent(`SpaceBetween),
        marginHorizontal(4),
      ];

    let inputWrapper =
      Style.[
        flexDirection(`Row),
        flexGrow(1),
        justifyContent(`FlexStart),
        alignItems(`Center),
        marginBottom(4),
      ];

    let paramWrapper =
      Style.[
        flexDirection(`Row),
        flexGrow(1),
        alignItems(`Center),
        justifyContent(`SpaceAround),
        backgroundColor(Color.rgba(0., 0., 0., 0.25)),
        border(~width=2, ~color=Color.rgba(0., 0., 0., 0.25)),
        borderRadius(4.),
        padding(4),
      ];

    let sliderLabelStyle =
      Style.[
        color(Colors.black),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(12),
      ];
    (
      hooks,
      <View style=fxContainer>
        <Center> <Text style=fxHeaderStyle text="MASTER FX" /> </Center>
        <View style=panelsStyle>
          <View style=panelStyle>
            <View style=inputWrapper>
              <Checkbox
                checked={appState.bitcrusherEnabled}
                onChange={() =>
                  parentDispatch(
                    ToggleBitcrusherEnabled(!appState.bitcrusherEnabled),
                  )
                }
                checkedColor={Color.hex("#F16F20")}
                style=checkboxStyle
              />
              <Text style=fxLabelStyle text="BITCRUSHER" />
            </View>
            <View style=paramWrapper>
              <View>
                <Knob
                  onValueChanged={v =>
                    parentDispatch(SetBitcrusherBitrate(v))
                  }
                  value={appState.bitcrusher.bitDepth}
                  maximumValue=32.
                  minimumValue=2.
                />
                <Center>
                  <Text style=sliderLabelStyle text="BIT DEPTH" />
                </Center>
              </View>
              <View>
                <Knob
                  onValueChanged={v =>
                    parentDispatch(SetBitcrusherSampling(int_of_float(v)))
                  }
                  value={float_of_int(appState.bitcrusher.downSampling)}
                  maximumValue=64.
                  minimumValue=1.
                />
                <Center>
                  <Text style=sliderLabelStyle text="DSAMPLE" />
                </Center>
              </View>
            </View>
          </View>
          <View style=panelStyle>
            <View style=inputWrapper>
              <Checkbox
                checked={appState.delayEnabled}
                onChange={() =>
                  parentDispatch(ToggleDelayEnabled(!appState.delayEnabled))
                }
                checkedColor={Color.hex("#F16F20")}
                style=checkboxStyle
              />
              <Text style=fxLabelStyle text="DELAY" />
            </View>
            <View style=paramWrapper>
              <View>
                <Knob
                  onValueChanged={v => parentDispatch(SetDelayDuration(v))}
                  value={appState.delay.duration}
                  maximumValue=0.5
                  minimumValue=0.01
                />
                <Center> <Text style=sliderLabelStyle text="DELAY" /> </Center>
              </View>
              <View>
                <Knob
                  onValueChanged={v => parentDispatch(SetDelayGain(v))}
                  value={appState.delay.gain}
                  maximumValue=0.9
                  minimumValue=0.01
                />
                <Center> <Text style=sliderLabelStyle text="GAIN" /> </Center>
              </View>
            </View>
          </View>
          <View style=panelStyle>
            <View style=inputWrapper>
              <Checkbox
                checked={appState.filterEnabled}
                onChange={() =>
                  parentDispatch(
                    ToggleFilterEnabled(!appState.filterEnabled),
                  )
                }
                checkedColor={Color.hex("#F16F20")}
                style=checkboxStyle
              />
              <Text style=fxLabelStyle text="FILTER" />
            </View>
            <View style=paramWrapper>
              <View>
                <Knob
                  onValueChanged={v =>
                    parentDispatch(
                      SetFilter(
                        Filter.create(
                          appState.filter.mode,
                          v /. sampleRate,
                          1.0,
                          0.0,
                        ),
                      ),
                    )
                  }
                  maximumValue=20000.
                  minimumValue=20.
                />
                <Center>
                  <Text style=sliderLabelStyle text="CUTOFF" />
                </Center>
              </View>
              <View>
                <View style=inputWrapper>
                  <Checkbox
                    checked={appState.filter.mode == Filter.LowPass}
                    onChange={a =>
                      parentDispatch(
                        SetFilter(
                          Filter.create(
                            Filter.LowPass,
                            appState.filter.fc,
                            1.0,
                            0.0,
                          ),
                        ),
                      )
                    }
                    checkedColor={Color.hex("#F16F20")}
                    style=checkboxStyle
                  />
                  <Text style=fxLabelStyle text="LOWPASS" />
                </View>
                <View style=inputWrapper>
                  <Checkbox
                    checked={appState.filter.mode == Filter.HighPass}
                    onChange={a =>
                      parentDispatch(
                        SetFilter(
                          Filter.create(
                            Filter.HighPass,
                            appState.filter.fc,
                            0.707,
                            0.0,
                          ),
                        ),
                      )
                    }
                    checkedColor={Color.hex("#F16F20")}
                    style=checkboxStyle
                  />
                  <Text style=fxLabelStyle text="HIGHPASS" />
                </View>
              </View>
            </View>
          </View>
        </View>
      </View>,
    );
  });