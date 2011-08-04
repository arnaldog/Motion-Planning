mData = load("bugtrapchico_hermite.csv");

[nRows, nColumns] = size(mData);

mOutput = mData(:, end);
mInput = mData(:,1:end-1);

# preparing the data
mInput = mInput';
mOutput = mOutput';

# SPLIT MATRIX IN 3 PIECES
# TRAIN, TEST, VALIDATE

nTrainSets = floor(nRows/3);
nTestSets = (nRows-nTrainSets)/3*2
nValiSets = nRows-nTrainSets-nTestSets;

## VALID INPUT
nValiInput = mInput(:, 1:nValiSets);
nValiOutput = mOutput(:, 1:nValiSets);

mInput(:, 1:nValiSets) = []
mOutput(:,1:nValiSets) = []

mTestInput = mInput(:, 1:nTestSets);
mTestOutput = mOutput(:,1:nTestSets);

mInput(:,1:nTestSets) = []
mOutput(:, 1:nTestSets) = []

mTrainInput = mInput(:, 1:nTrainSets);
mTrainOutput = mOutput(:, 1:nTrainSets);

[mTrainInputN, cMeanInput, cStdInput] = prestd(mTrainInput);

mMinMaxElements = min_max(mTrainInput);

nHiddenNeurons = 1;
nOutputNeurons = 1;

MLPnet = newff(mMinMaxElements, [nHiddenNeurons nOutputNeurons], {"tansig", "purelin"}, "trainlm", "", "mse");

#saveMLPStruct(MLPnet, "MLP3test.txt");

#define validation data new
VV.P = nValiInput;
VV.T = nValiOutput;

VV.P = trastd(VV.P, cMeanInput, cStdInput);

[net] = train(MLPnet, mTrainInputN, mTrainOutput, [], [], VV);

[mTestInputN] = trastd(mTestInput, cMeanInput, cStdInput);

[simOut] = sim(net, mTestInputN);
simOut








