#include "Sampler.h"
#include "Random.h"
#include "Constants.h"

Sampler::Sampler(): numSamples(1), numSets(1), count(0), jump(0) {
}

Sampler::Sampler(const int &n): numSamples(n), numSets(1), count(0), jump(0) {
}

Sampler::~Sampler() {
}

Point2D Sampler::sampleUnitSquare() {
	if( count % numSamples == 0) { // every time a new Sampler selected
		jump = (Random::rand_int() % numSets) * numSamples;
	}

	// to differentiate in adjacent pixels
	//return (samples[jump + count++ % numSamples]);
	return (samples[jump + shuffledIndices[jump + count++ % numSamples]]); // after shuffling
}

void Sampler::setupShuffledIndices() {
	shuffledIndices.reserve(numSamples * numSets);
	vector <int> indices;

	for(int j = 0; j < numSamples; j++) {
		indices.push_back(j);
	}

	for(int p = 0; p < numSets; p++) {
		random_shuffle(indices.begin(), indices.end());

		for(int j = 0; j < numSamples; j++) {
			shuffledIndices.push_back(indices[j]);
		}
	}
}

void Sampler::setNumSets(const int &num_s) {
	numSets = num_s;
}

int Sampler::getNumSamples() const {
	return numSamples;
}

int Sampler::getNumSets() const {
	return numSets;
}

void Sampler::shuffleXCoordinates() {
	for(int p = 0; p < numSets; p++) {
		for(int i = 0; i < numSamples; i++) {
			int dest = Random::rand_int() % numSamples + p * numSamples;
			swap(samples[p * numSamples + i].first, samples[dest].first);
		}
	}
}

void Sampler::shuffleYCoordinates() {
	for(int p = 0; p < numSets; p++) {
		for(int i = 0; i < numSamples; i++) {
			int dest = Random::rand_int() % numSamples + p * numSamples;
			swap(samples[p * numSamples + i].second, samples[dest].second);
		}
	}
}

void Sampler::mapSamplesToUnitDisk() {
	int size = samples.size();
	RTdouble phi, r;
	Point2D sp;
	diskSamples.reserve(size);
	for(int j = 0; j < size; j++) {
		// from [0,1]^2 to [-1,1]^2

		sp.first = 2. * samples[j].first - 1.;
		sp.second = 2. * samples[j].second - 1.;
		if(sp.first > -sp.second) {
			if(sp.first > sp.second) {
				r = sp.first;
				phi = sp.second / sp.first;
			}
			else {
				r = sp.second;
				phi = 2. - sp.first / sp.second;
			}
		}
		else {
			if(sp.first < sp.second) {
				r = -sp.first;
				phi = 4. + sp.second / sp.first;
			}
			else {
				r = -sp.second;
				if( sp.second != RT_ZERO) {
					phi = 6 - sp.first / sp.second;
				}
				else {
					phi = RT_ZERO;
				}
			}
		}
		phi *= RT_PI / 4.;
		/*infoPrint("sp.x: " + to_string(sp.first));
		infoPrint("sp.y: " + to_string(sp.second));
		infoPrint("phi: " + to_string(phi));*/
		//infoPrint("atan2: " + to_string(atan2(sp.second, sp.first) + 2.*RT_PI));
		diskSamples[j].first = r * cos(phi);
		diskSamples[j].second = r * sin(phi);
	}
}


void Sampler::mapSamplesToHemisphere(const RTdouble &e) {
	int size = samples.size();
	hemisphereSamples.reserve(numSamples * numSets);
	for(int j = 0; j < size; j++) {
		RTdouble cosPhi = cos(2. * RT_PI * samples[j].first);
		RTdouble sinPhi = sin(2. * RT_PI * samples[j].first);
		RTdouble cosTheta = pow((RT_ONE - samples[j].second), RT_ONE / (e + RT_ONE));
		RTdouble sinTheta = sqrt(RT_ONE - cosTheta * cosTheta);

		hemisphereSamples.push_back(Point(sinTheta*cosPhi, sinTheta*sinPhi, cosTheta));
		//hemisphereSamples.push_back(Point(sinTheta*cosPhi, cosTheta, sinTheta*sinPhi));
	}
	/*for(int i = 0; i < numSamples; i++) {
		infoPrint("square sample: (" + to_string(samples[i].first) + ", " + to_string(samples[i].second) + ")");
		infoPrint("hemi sample: " + hemisphereSamples[i].to_rep());
	}*/

	/*for(auto iter = hemisphereSamples.begin(); iter != hemisphereSamples.end(); iter++) {
		infoPrint(iter->to_rep());
		//infoPrint(to_string(iter->distance(Point(RT_ZERO))));
	}*/
}

Point Sampler::sampleHemisphere() {
	if( count % numSamples == 0) { // every time a new Sampler selected
		jump = (Random::rand_int() % numSets) * numSamples;
	}

	// to differentiate in adjacent pixels
	//return (samples[jump + count++ % numSamples]);
	return (hemisphereSamples[jump + shuffledIndices[jump + count++ % numSamples]]); // after shuffling
}

Jittered::Jittered(): Sampler() {
}

Jittered::Jittered(const int &n): Sampler(n) {
}

Jittered::~Jittered() {
}

void Jittered::generateSamples() {
	int n = (int) sqrt(numSamples);
	for(int p = 0; p < numSets; p++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				Point2D sp = make_pair((k + Random::rand_float()) / n, (j + Random::rand_float()) / n);
				samples.push_back(sp);
			}
		}
	}
}

Regular::Regular(): Sampler() {
}

Regular::Regular(const int &n): Sampler(n) {
}

Regular::~Regular() {
}

void Regular::generateSamples() {
	int n = (int) sqrt(numSamples);
	for(int p = 0; p < numSets; p++) {
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				Point2D sp = make_pair((k+RT_ONE) / (n+RT_ONE), (j+RT_ONE) / (n+RT_ONE));
				//Point2D sp = make_pair((k+RT_ZERO) / (n), (j+RT_ZERO) / (n));
				samples.push_back(sp);
				//printf("(%.3lf, %.3lf)\n", sp.first, sp.second);
				//infoPrint("sample point: " + to_string(sp.first) + ", " + to_string(sp.second));
			}
		}
	}
}

NRooks::NRooks(): Sampler() {
}

NRooks::NRooks(const int &n): Sampler(n) {
}

NRooks::~NRooks() {
}

void NRooks::generateSamples() {
	for(int p = 0; p < numSets; p++) {
		for(int j = 0; j < numSamples; j++) { // along the diagonal
			Point2D pv;
			pv.first = (j + Random::rand_float()) / numSamples;
			pv.second = (j + Random::rand_float()) / numSamples;
			samples.push_back(pv);
		}
	}

	shuffleXCoordinates();
	shuffleYCoordinates();
}

MultiJittered::MultiJittered(): Sampler() {
}

MultiJittered::MultiJittered(const int &n): Sampler(n) {
}

MultiJittered::~MultiJittered() {
}

void MultiJittered::generateSamples() {
	int n = (int) sqrt(numSamples);
	for(int p = 0; p < numSets; p++) {
		for(int j = 0; j < numSamples; j++) { // along the diagonal
			Point2D pv;
			//pv.first = (j + Random::rand_float()) / numSamples;
			pv.first = (((j % n) * n + j / n) + Random::rand_float()) / numSamples;
			pv.second = (j + Random::rand_float()) / numSamples;
			samples.push_back(pv);
		}
	}

	shuffleXCoordinates();
	shuffleYCoordinates();
}
