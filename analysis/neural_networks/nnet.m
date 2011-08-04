#mData = load("mData.txt");
mData = load("bugtrapchico_hermite.csv");

[nRows, nColumns] = size(mData);

mOutput = mData(:, end);
mInput = mData(:,1:end-1);

#dividir en 3 partes
[mTrain,mTest,mVali] = subset(mData',1,2);

[mTrainInputN,cMeanInput,cStdInput] = prestd(mTrain(1:end-1,:));

mMinMaxElements = min_max(mTrainInputN);

nHiddenNeurons = 20;
nOutputNeurons = 1;

MLPnet = newff(mMinMaxElements, [nHiddenNeurons nOutputNeurons], {"tansig", "purelin"}, "trainlm", "", "mse");

MLPnet.trainParam.epochs = 100;
MLPnet.trainParam.goal = 0.1;

#saveMLPStruct(MLPnet, "MLP3test.txt");


VV.P = mVali(1:end-1,:);
VV.T = mVali(end,:);

#standardize also the validate data
VV.P = trastd(VV.P,cMeanInput,cStdInput);

[net] = train(MLPnet,mTrainInputN,mTrain(end,:),[],[],VV);

# make preparations for net test and test MLPnet
# standardise input & output test data
[mTestInputN] = trastd(mTest(1:end-1,:),cMeanInput,cStdInput);

[simOut] = sim(net,mTestInputN);
simOut;

[m n] = size(simOut);
[x y] = size(mTest(end,:));

#plot(1:n, simOut, 1:n, mTest(1:end-1,:));

aaa = simOut;
bbb = mTest(end,:);
#bbb = bbb';

aaa(:,1:3)
bbb(:,1:3)
