clc,clear
%%change the file paths when needed
subplot(2,1,1);
M = csvread('training_data.csv');
histogram(M,500);
title("Distribution of training price");
xlabel("Price");
ylabel("Frequency");

subplot(2,1,2);
N=csvread('D:\School\USC\Spring 2018\Math512\project\Project\Project\Simulated Price.csv');
histogram(N(:,1:252),500);
title("Distribution of simulated price");
xlabel("Price");
ylabel("Frequency");